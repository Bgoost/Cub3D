/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/02/12 15:25:52 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdint.h>

# define MAP_HEIGHT 22
# define MAP_WIDTH 21
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

char	**hardcode_map(int height, int width, int fd)
{
	int	x;
	int	i;
	char	*line;
	char	**map;

	x = 0;
	line = NULL;
	map = NULL;
	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	while (x < height)
	{
		map[x] = malloc(sizeof(char) * (width + 1));
		if (!map[x])
			return (free(map), ft_putstr_fd("malloc error\n", 2), NULL);
		x++;
	}
	map[x] = NULL;
	x = 0;
	while (x < height)
	{
		i = 0;
		line = get_next_line(fd);
		while (line[i])
		{
			map[x][i] = line[i];
			i++;
		}
		map[x][i] = '\0';
		x++;
	}
	// printing map
	x = 0;
	while (map[x])
	{
		printf("map[%d]: %s", x, map[x]);
		x++;
	}
	return (map);
}

double	degree_to_radian(double degree)
{
	double	radian;
	
	radian = (degree * M_PI) / (double)180.0;
	return (radian);
}

int	hardcode_info(t_raycasting *info)
{
	info->ray_increment = (double)FOV / (double)WIDTH;
	info->distance_to_plane = (WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	info->direction = 90;
	info->player.x = 3;
	info->player.y = 20;
	info->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!info->mlx)
		return (1);
	info->image = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!info->image)
	{
		free(info->mlx);
		return (1);
	}
	//printing info
	printf("\nFOV: %d\n", FOV);
	printf("WINDOW HEIGHT: %d\n", HEIGHT);
	printf("WINDOW WIDTH: %d\n", WIDTH);
	printf("\nray increment: %f\n", info->ray_increment);
	printf("distance_to_plane: %f\n", info->distance_to_plane);
	printf("player direction: %f\n", info->direction);
	printf("player X: %f\n", info->player.x);
	printf("player Y: %f\n\n", info->player.y);
	return (0);
}

t_point	*first_h_hit(double angle, t_point player)
{
	t_point	grid_player;
	t_point	*hit;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE + TILE / 2;
	grid_player.y = player.y * TILE + TILE / 2;
	
	if (angle <= 180 && angle >= 0)
		hit->y = floor(grid_player.y / TILE) * TILE - 0.000000000001; 
	else
		hit->y = floor(grid_player.y / TILE) * TILE + TILE; 
	hit->x = grid_player.x + (grid_player.y - hit->y) / tan(degree_to_radian(angle));
	
//	printf("1st hit: P(%f, %f)\n", hit->x, hit->y);
//	printf("scaled down: P(%d, %d)\n", (int)hit->x / TILE, (int)hit->y / TILE);
	return (hit);
}

void	horizontal_increments(double angle, t_point *increment)
{
	if (angle >= 0 && angle <= 180) // if ray looks UP 
		increment->y = -TILE;
	else
		increment->y = TILE;
	if (angle >= 90 && angle <= 270) // if ray looks LEFT
		increment->x = -fabs(TILE / tan(degree_to_radian(angle)));
	else
		increment->x = fabs(TILE / tan(degree_to_radian(angle)));
//	printf("x_increment = %f\ny_increment = %f\n\n", increment->x, increment->y);
}

int	safe_point(double x, double y)
{
	if ((int)x / TILE < 0 || ((int)x / TILE) >= MAP_WIDTH)
	{
//		printf("x out of bounds\n");
		return (0);
	}
	if ((int)y / TILE < 0 || ((int)y / TILE) >= MAP_HEIGHT)
	{
//		printf("y out of bounds\n");
		return (0);
	}
	return (1);
}

int	safe_point2(double x, double y)
{
	if (x < 0 || ((int)x / TILE) >= MAP_WIDTH)
	{
//		printf("x out of bounds\n");
		return (0);
	}
	if (y < 0 || ((int)y / TILE) >= MAP_HEIGHT)
	{
//		printf("y out of bounds\n");
		return (0);
	}
	return (1);
}

t_point	*horizontal_hit(t_point player, char **map, double angle)
{
	t_point	*hit;
	t_point	increment;

	printf("HORIZONTAL HITS\n");	
	hit = first_h_hit(angle, player);
	if (!hit)
		return (NULL);
	if (!safe_point(hit->x, hit->y))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1') // we find WALL, we stop
		return (printf("theres a wall in first point\n"), hit);
	horizontal_increments(angle, &increment);
	while (map[(int)hit->y / TILE][(int)hit->x / TILE] == '0') 
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);
		if (!safe_point(hit->x, hit->y))
			return (hit);
	}
	return (hit);
}

t_point	*first_v_hit(double angle, t_point player)
{
	t_point	*hit;
	t_point	grid_player;
	
	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE + TILE / 2;
	grid_player.y = player.y * TILE + TILE / 2;

	if (angle <= 270 && angle >= 90) // if angle looks LEFT
		hit->x = floor(grid_player.x / TILE) * TILE - 0.0000000000001; 
	else
		hit->x = floor(grid_player.x / TILE) * TILE + TILE;
	hit->y = grid_player.y + (grid_player.x - hit->x) * tan(degree_to_radian(angle));

//	printf("1st hit: P(%f, %f)\n", hit->x, hit->y);
//	printf("scaled down: P(%d, %d)\n", (int)hit->x / TILE, (int)hit->y / TILE);
	return (hit);
}

void	vertical_increment(double angle, t_point *increment)
{
	if (angle <= 270 && angle >= 90) // if angle looks LEFT
		increment->x = -TILE;
	else
		increment->x = TILE;

	if (angle <= 180 && angle >= 0) // if angle looks UP
		increment->y = -fabs(TILE * tan(degree_to_radian(angle)));
	else
		increment->y = fabs(TILE * tan(degree_to_radian(angle)));
//	printf("x_increment = %f\ny_increment = %f\n\n", increment->x, increment->y);
}

t_point	*vertical_hit(t_point player, char **map, double angle)
{
	t_point	*hit;
	t_point	increment;

	printf("VERTICAL HITS\n");	
	hit = first_v_hit(angle, player);	
	if (!hit)
		return (NULL);
	if (!safe_point(hit->x, hit->y))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
		return (printf("theres a wall in first point\n"), hit);
	vertical_increment(angle, &increment);
	while (map[((int)hit->y / TILE)][(int)hit->x / TILE] == '0')
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);
		if (!safe_point(hit->x, hit->y))
			return (hit);
	}
	return (hit);
}

double	point_distance(t_point hit, t_point player, char point)
{
	(void)point;
	double	distance;
	
	player.x = player.x * TILE + TILE / 2;
	player.y = player.y * TILE + TILE / 2;

	distance = sqrt(pow((player.x - hit.x), 2) + pow((player.y - hit.y), 2));
//	printf("%c distance: %f\n", point, distance);
	return (distance);
}

void	find_distance(t_point *v_hit, t_point *h_hit, t_ray *ray, t_raycasting *info)
{
	double	v_distance;
	double	h_distance;
	
	printf("DISTANCE\n");	
   	// find distance from player to each hit point (vertical & horizontal)
	if (v_hit->y < 0 || ((int)v_hit->y / TILE) > MAP_HEIGHT || v_hit->x < 0 || ((int)v_hit->x / TILE) > MAP_WIDTH)
		v_distance = DOUBLE_MAX;
	else
		v_distance = point_distance(*v_hit, info->player, 'v');
	
	if (h_hit->y < 0 || ((int)h_hit->y / TILE) > MAP_HEIGHT || h_hit->x < 0 || ((int)h_hit->x / TILE) > MAP_WIDTH)
		h_distance = DOUBLE_MAX;
	else
		h_distance = point_distance(*h_hit, info->player, 'h');
	
	// save shortest distance
	if (v_distance < h_distance)
	{
		ray->distance_to_wall = v_distance;
		ray->hit_point = v_hit;
		ray->wall_hit = 'v';
	}
	else
	{
		ray->distance_to_wall = h_distance;
		ray->hit_point = h_hit;
		ray->wall_hit = 'h';
	}
	printf("\nfinal distance to wall: %f\n", ray->distance_to_wall);
	
	// OJO DE PEZ
//	printf("\nFISHEYE CORRECTION\n");	
	ray->distance_to_wall = ray->distance_to_wall * cos(degree_to_radian(ray->angle - info->direction));
	printf("corrected distance to wall: %f\n", ray->distance_to_wall);
}

void	cast_ray(t_raycasting *info, char **map, t_ray *ray)
{
	t_point	*v_hit;
	t_point	*h_hit;


	printf("\n\nANGLE %f\n-------------------------\n", ray->angle);
	printf("player: (%f, %f)\n", info->player.x, info->player.y);
	// HORIZONTAL intersections
	h_hit = horizontal_hit(info->player, map, ray->angle);
	printf("h hit: (%f, %f)\n", h_hit->x, h_hit->y);
	printf("scaled down: (%d, %d)\n\n", (int)h_hit->x / TILE, (int)h_hit->y / TILE);

	// VERTICAL intersections
	v_hit = vertical_hit(info->player, map, ray->angle);
	printf("v hit: (%f, %f)\n", v_hit->x, v_hit->y);
	printf("scaled down: (%d, %d)\n\n", (int)v_hit->x / TILE, (int)v_hit->y / TILE);
	
	// calculating DISTANCE of each and choosing the shortest
	find_distance(v_hit, h_hit, ray, info);

	//	Find projected wall height
	//  FORMULA
 	//  Projected Wall Height = (real wall height / distance to wall) * distance to projection plane
	ray->projection_height = (TILE / ray->distance_to_wall) * info->distance_to_plane;
//	printf("\nprojection height: %f\n", ray->projection_height);

	// Function to check the value is correct		
//	printf("test.1: %f\n", ray->projection_height / info->distance_to_plane);
//	printf("test.2: %f\n", TILE / ray->distance_to_wall);
	if ((ray->projection_height / info->distance_to_plane) - (TILE / ray->distance_to_wall) > 0.00001)
	   printf("ERROR with projection heigth!\n");

	ray->projection_height = ceil(ray->projection_height); // round UP 
	printf("\nprojection height rounded UP: %f\n", ray->projection_height);

	// Find first wall pixel
	t_point	center;

	center.x = WIDTH / 2;
	center.y = HEIGHT / 2;

	ray->first_wall_pixel = center.y - (ray->projection_height / 2);
	printf("\nfirst_wall_pixel: %d\n", ray->first_wall_pixel);

	// Find last wall pixel
	ray->last_wall_pixel = ray->first_wall_pixel + ray->projection_height;
	printf("last_wall_pixel: %d\n", ray->last_wall_pixel);
	
	
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, double x, double y)
{
	/*double	pixel;

	pixel = texture->pixels[y * texture->width + x];
	return (pixel);*/
	int		pixel_index; 
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

 	printf("y: %f, x: %f, width: %d\n", y, x, texture->width); 

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0x00000000; //transparent black
	
	pixel_index = (y * texture->width + x) * 4; // 4 = bytes por pixel
    
	r = texture->pixels[pixel_index];     
    g = texture->pixels[pixel_index + 1];
    b = texture->pixels[pixel_index + 2];
    a = texture->pixels[pixel_index + 3];
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

void	print_column(t_ray *ray, mlx_image_t *image, int x)
{
	int				y;
//	uint32_t		texture_color;
//	double			text_pos;
//	double 			step;
//	mlx_texture_t	*texture;
//	t_point			texture_in;
	
	y = 0;
	while (y < HEIGHT) // print column
	{
		if (y < ray->first_wall_pixel)
			mlx_put_pixel(image, x, y, CEILING_COLOR);
		else if (y >= ray->first_wall_pixel && y <= ray->last_wall_pixel)
		{
		// TEXTURES
/*			texture = mlx_load_png("./textures/BRICK_1A.PNG");
			if (!texture)
				ft_putstr_fd("Failed to load textures\n", 2);

			step = (double)TEXTURE_HEIGHT / ray->projection_height;
			text_pos = (ray->first_wall_pixel - HEIGHT / 2 + ray->projection_height / 2) * step;
			
			if (ray->wall_hit == 'v')
				texture_in.x = ray->hit_point->y - floor(ray->hit_point->y);
			else
				texture_in.x = ray->hit_point->x - floor(ray->hit_point->x);
			
 	//		printf("texture_in x: %f\n", texture_in.x); 
			texture_in.x = texture_in.x * TEXTURE_WIDTH;
 			printf("texture_in x: %f\n", texture_in.x); 
			while (y < ray->last_wall_pixel) 
			{
				texture_in.y = (int)text_pos % TEXTURE_HEIGHT;
// 				printf("first y: %f, x: %f, width: %d\n", texture_in.y, texture_in.x, texture->width); 
				text_pos += step;
 	//			printf("first texture_pos: %f\n\n", text_pos); 
				texture_color = get_texture_pixel(texture, x, texture_in.y);
 //				printf("\ntexture color: %u\n\n", texture_color); 
				mlx_put_pixel(image, x, y, texture_color);
				y++;
			}*/
			mlx_put_pixel(image, x, y, WALL_COLOR);
		}
		else
			mlx_put_pixel(image, x, y, FLOOR_COLOR);
		y++;
	}
}

double	adjust_angle(double angle)
{
	double res;

	res = 0;
	res = fmod(angle, 360.0);
	if (res <= 0.0)
		res = res + 360.0;	
//	printf("angle: %f\n", angle);
//	printf("res: %f\n", res);
   	return (res);	
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_scene(t_raycasting *info, char **map, t_ray *ray)
{
	int		x;
	int		y;
	
	x = 0;
	y = 0;
	ray->angle = info->direction + (FOV / 2);
	ray->angle = adjust_angle(ray->angle);
	printf("direction = %f\n", info->direction);
	while (x < WIDTH)
	{
		y = 0;
		cast_ray(info, map, ray);
		print_column(ray, info->image, x);
		ray->angle = ray->angle - info->ray_increment;
		ray->angle = adjust_angle(ray->angle);	
		x++;
	}
	if (mlx_image_to_window(info->mlx, info->image, 0, 0) == -1)
	{
		mlx_close_window(info->mlx);
		//free
		exit(1);
	}
}

void	keyboard_input(mlx_key_data_t keydata, void *param)
{
	mlx_t			*mlx;
	t_raycasting	*info;
	t_point			tmp;
	
	info = (t_raycasting *)param;
	mlx = (mlx_t *)info->mlx;

	tmp = info->player;
	printf("key = %d\n", keydata.key);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		//delete texture & free everything
		mlx_delete_image(mlx, info->image);
		mlx_close_window(mlx);
		exit(0);
	}
	// ROTACIÓN FOV (flechitas)
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		info->direction += 10;
		print_scene(info, info->map, info->ray);
	}	
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 10;
		print_scene(info, info->map, info->ray);
	}	
	// MOVIMIENTOS (WSAD)
	// no estan bien, hay que moverse segun el ángulo del personaje!!
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		tmp.y -= 0.5 * sin(degree_to_radian(info->direction));
		// restamos porque cuando los rayos miran abajo, sin es negativo y como queremos avanzar, la y será positiva
		tmp.x += 0.5 * cos(degree_to_radian(info->direction));
		// tenemos que sumar en player.x porque el resultado de cos puede ser negativo(cuando rayo mira a la izquierda) o positivo
		if (safe_point2(tmp.x, tmp.y))
		{
			info->player = tmp;
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		tmp.y += 0.5 * sin(degree_to_radian(info->direction));
		tmp.x -= 0.5 * cos(degree_to_radian(info->direction));
		if (safe_point2(tmp.x, tmp.y))
		{
			info->player = tmp;
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		tmp.x -= 0.5 * sin(degree_to_radian(info->direction));
		tmp.y -= 0.5 * cos(degree_to_radian(info->direction));
		if (safe_point2(tmp.x, tmp.y))
		{
			info->player = tmp;
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		tmp.x += 0.5 * sin(degree_to_radian(info->direction));
		tmp.y += 0.5 * cos(degree_to_radian(info->direction));
		if (safe_point2(tmp.x, tmp.y))
		{
			info->player = tmp;
			print_scene(info, info->map, info->ray);
		}
	}
}

void	free_game(t_raycasting *game)
{
//	free(game->image);
//	free(game->mlx);
    mlx_terminate(game->mlx);
	free_array(game->map);
	free(game->ray);
	free(game);
}

int	main(int argc, char **argv)
{
	(void)argc;
	int				fd;
	t_raycasting	*info;

	fd = -1;
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		return(ft_putstr_fd("failed to open file\n", 2), 1);
	info = malloc(sizeof(t_raycasting) * 1);
	if (!info)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	info->map = hardcode_map(MAP_HEIGHT, MAP_WIDTH, fd);
	
	if (hardcode_info(info) == 1)
		return (ft_putstr_fd("malloc error\n", 2), 1);
	
	info->ray = malloc(sizeof(t_ray) * 1);
	if (!info->ray)
	{
		free_array(info->map);
		return (ft_putstr_fd("malloc error\n", 2), 1);
	}

	print_scene(info, info->map, info->ray);
	mlx_key_hook(info->mlx, keyboard_input, info);
	mlx_loop(info->mlx);
	free_game(info);
	return (0);
}
