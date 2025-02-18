/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/02/18 19:54:23 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*char	**hardcode_map(int height, int width, int fd)
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
}*/

double	degree_to_radian(double degree)
{
	double	radian;
	
	radian = (degree * M_PI) / (double)180.0;
	return (radian);
}

/*int	hardcode_info(t_raycasting *info)
{
	info->ray_increment = (double)FOV / (double)WIN_WIDTH;
	info->distance_to_plane = (WIN_WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	info->direction = 90;
	info->player.x = 3;
	info->player.y = 20;
	info->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", false);
    if (!info->mlx)
		return (1);
	info->image = mlx_new_image(info->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!info->image)
	{
		free(info->mlx);
		return (1);
	}
	//printing info
	printf("\nFOV: %d\n", FOV);
	printf("WINDOW HEIGHT: %d\n", WIN_HEIGHT);
	printf("WINDOW WIDTH: %d\n", WIN_WIDTH);
	printf("\nray increment: %f\n", info->ray_increment);
	printf("distance_to_plane: %f\n", info->distance_to_plane);
	printf("player direction: %f\n", info->direction);
	printf("player X: %f\n", info->player.x);
	printf("player Y: %f\n\n", info->player.y);
	return (0);
}*/

t_point	*first_h_hit(double angle, t_point player)
{
	t_point	grid_player;
	t_point	*hit;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE + TILE / 2;
	grid_player.y = player.y * TILE + TILE / 2;
	
//	printf("grid player: (%f, %f)\n", grid_player.x, grid_player.y);
	
	if (angle <= 180 && angle >= 0)
		hit->y = floor(grid_player.y / TILE) * TILE - 0.0000000001; 
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

int	safe_point(double x, double y, int width, int height)
{
	if ((int)x / TILE < 0 || ((int)x / TILE) >= width)
	{
//		printf("x out of bounds\n");
		return (0);
	}
	if ((int)y / TILE < 0 || ((int)y / TILE) >= height)
	{
//		printf("y out of bounds\n");
		return (0);
	}
	return (1);
}

int	is_wall(double x, double y, char **map)
{
	int	x_;
	int	y_;

	x_ = (int)floor(x);
	y_ = (int)floor(y);
	if (map[y_ - 1][x_ - 1] == '1')
	{
		printf("wall found at x = %f y = %f\n", x, y);
		return (1);
	}
	return (0);
}

int	safe_point2(double x, double y, int width, int height)
{

	if (x < 0 || ceil(x) >= width)
	{
//		printf("x out of bounds\n");
		return (0);
	}
	if (y < 0 || ceil(y) >= height)
	{
//		printf("y out of bounds\n");
		return (0);
	}
	return (1);
}

t_point	*horizontal_hit(t_point player, char **map, double angle, t_raycasting *info)
{
	t_point	*hit;
	t_point	increment;

//	printf("HORIZONTAL HITS\n");	
	hit = first_h_hit(angle, player);
	if (!hit)
		return (NULL);
	if (!safe_point(hit->x, hit->y, info->map_width, info->map_height))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1') // we find WALL, we stop
	{															
//		printf("theres a wall in first point\n");
		return (hit);
	}
	horizontal_increments(angle, &increment);
	while (map[(int)hit->y / TILE][(int)hit->x / TILE] == '0') 
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);
		if (!safe_point(hit->x, hit->y, info->map_width, info->map_height))
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
		hit->x = floor(grid_player.x / TILE) * TILE - 0.0000000001; 
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

t_point	*vertical_hit(t_point player, char **map, double angle, t_raycasting *info)
{
	t_point	*hit;
	t_point	increment;

//	printf("VERTICAL HITS\n");	
	hit = first_v_hit(angle, player);	
	if (!hit)
		return (NULL);
	if (!safe_point(hit->x, hit->y, info->map_width, info->map_height))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
	{
//		printf("theres a wall in first point\n");
		return (hit);
	}
	vertical_increment(angle, &increment);
	while (map[((int)hit->y / TILE)][(int)hit->x / TILE] == '0')
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);
		if (!safe_point(hit->x, hit->y, info->map_width, info->map_height))
			return (hit);
	}
	return (hit);
}

double	point_distance(t_point hit, t_point player, char point)
{
	(void)point;
	double	distance;
	t_point	grid_player;
	
	grid_player.x = (player.x * TILE) + (TILE / 2);
	grid_player.y = (player.y * TILE) + (TILE / 2);

	distance = sqrt(pow((grid_player.x - hit.x), 2) + pow((grid_player.y - hit.y), 2));
//	printf("%c distance: %f\n", point, distance);
	return (distance);
}

void	find_distance(t_point *v_hit, t_point *h_hit, t_ray *ray, t_raycasting *info)
{
	double	v_distance;
	double	h_distance;
	
//	printf("DISTANCE\n");	
   	// find distance from player to each hit point (vertical & horizontal)
	if (v_hit->y < 0 || ((int)v_hit->y / TILE) > info->map_height || v_hit->x < 0 || ((int)v_hit->x / TILE) > info->map_width)
		v_distance = DOUBLE_MAX;
	else
		v_distance = point_distance(*v_hit, info->player, 'v');
	
	if (h_hit->y < 0 || ((int)h_hit->y / TILE) > info->map_height || h_hit->x < 0 || ((int)h_hit->x / TILE) > info->map_width)
		h_distance = DOUBLE_MAX;
	else
		h_distance = point_distance(*h_hit, info->player, 'h');
	
	// save shortest distance
	if (v_distance < h_distance)
	{
		ray->distance_to_wall = v_distance;
		ray->hit_point = v_hit;
		ray->wall_hit = 'v';
		free(h_hit);
	}
	else
	{
		ray->distance_to_wall = h_distance;
		ray->hit_point = h_hit;
		ray->wall_hit = 'h';
		free(v_hit);
	}
//	printf("wall hit =  %c\n", ray->wall_hit);
//	printf("\nfinal distance to wall: %f\n", ray->distance_to_wall);
	
	// OJO DE PEZ
//	printf("\nFISHEYE CORRECTION\n");	
	ray->distance_to_wall = ray->distance_to_wall * cos(degree_to_radian(ray->angle - info->direction));
//	printf("corrected distance to wall: %f\n", ray->distance_to_wall);
}

int	cast_ray(t_raycasting *info, char **map, t_ray *ray)
{
	t_point	*v_hit;
	t_point	*h_hit;
	t_point	center;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;

//	printf("\n\nANGLE %f\n-------------------------\n", ray->angle);
//	printf("map player in double: (%f, %f)\n", info->player.x, info->player.y);
	h_hit = horizontal_hit(info->player, map, ray->angle, info);
	if (!h_hit) 
		return (0); // malloc error
	v_hit = vertical_hit(info->player, map, ray->angle, info);
	if (!v_hit)
		return (free(h_hit), 0); // malloc error
	find_distance(v_hit, h_hit, ray, info);
 
	//  Projected Wall Height = (real wall height / distance to wall) * distance to projection plane
	ray->projection_height = (TILE / ray->distance_to_wall) * info->distance_to_plane;

//	printf("\nprojection height: %f\n", ray->projection_height);
	
//	printf("test.1: %f\n", ray->projection_height / info->distance_to_plane);
//	printf("test.2: %f\n", TILE / ray->distance_to_wall);

	if ((ray->projection_height / info->distance_to_plane) - (TILE / ray->distance_to_wall) > 0.0001)
	{
	 	ft_putstr_fd("ERROR with projection heigth!\n", 2);
		exit (1);
	}


	ray->projection_height = ceil(ray->projection_height); // round UP 
//	printf("\nprojection height rounded UP: %f\n", ray->projection_height);

	ray->first_wall_pixel = center.y - (ray->projection_height / 2);
//	printf("\nfirst_wall_pixel: %d\n", ray->first_wall_pixel);

	ray->last_wall_pixel = ray->first_wall_pixel + ray->projection_height;
//	printf("last_wall_pixel: %d\n", ray->last_wall_pixel);

	if (ray->projection_height > WIN_HEIGHT - 1 || ray->projection_height < 0)
		adjust_pixels(&ray->first_wall_pixel, &ray->last_wall_pixel);
//	printf("FIRST pixels modified: %d\n", ray->first_wall_pixel);
//	printf("LAST pixels modified: %d\n", ray->last_wall_pixel);
	return (1);
}

void	print_column(t_ray *ray, t_raycasting *info, int x)
{
	int				y;
	uint32_t		texture_color;
	double			text_pos;
	double 			step;
	t_point			texture_in;
	
	y = 0;
	ray->wall_texture = get_wall_texture(ray, info->textures);
	if (!ray->wall_texture)
	{
		//mlx_load_image failed
		exit(1);	
	}	

	step = (double)ray->wall_texture->height / ray->projection_height;
	text_pos = (ray->first_wall_pixel - WIN_HEIGHT / 2 + ray->projection_height / 2) * step;

	if (ray->wall_hit == 'v')
		texture_in.x = fmod(ray->hit_point->y, TILE);
	else 
		texture_in.x = fmod(ray->hit_point->x, TILE);
	texture_in.x = (texture_in.x / TILE) * ray->wall_texture->width;

	// No veo que cambie nada si lo pongo
//	texture_in.x = (int)texture_in.x % ray->wall_texture->width;
//	if (texture_in.x < 0)
//		texture_in.x += ray->wall_texture->width;


	while (y < WIN_HEIGHT - 1) // print column
	{
		if (y < ray->first_wall_pixel)
			mlx_put_pixel(info->image, x, y, info->ceiling_color);
		else if (y >= ray->first_wall_pixel && y <= ray->last_wall_pixel)
		{
			while (y < ray->last_wall_pixel) 
			{
				texture_in.y = (int)text_pos % ray->wall_texture->height;
				if (texture_in.y < 0)
					texture_in.y += ray->wall_texture->height;

				text_pos += step;
				//printf("pixel %d\ntexture_in.x: %f, texture_in.y: %f, text_pos: %f, step: %f\n", y, texture_in.x, texture_in.y, text_pos, step);
				
				texture_color = get_texture_pixel(ray->wall_texture, texture_in.x, texture_in.y);
				mlx_put_pixel(info->image, x, y, texture_color);
				if (y >= WIN_HEIGHT - 1)
					return ;
				y++;
			}
			mlx_put_pixel(info->image, x, y, WALL_COLOR);
		}
		else
			mlx_put_pixel(info->image, x, y, info->floor_color);
		y++;
	}
	mlx_delete_texture(ray->wall_texture);
}

double	adjust_angle(double angle)
{
	double res;

	res = 0;
	res = fmod(angle, 360.0);
	if (res <= 0.0)
		res = res + 360.0;
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
	info->ceiling_color = get_ceiling_color(info->textures.ceiling_color);
	info->floor_color = get_floor_color(info->textures.floor_color);
	while (x < WIN_WIDTH - 1)
	{
		y = 0;
		ray->angle = adjust_angle(ray->angle);
		if (!cast_ray(info, map, ray)) // malloc error
			exit (1);
		print_column(ray, info, x);
		free(ray->hit_point);
		ray->angle = ray->angle - info->ray_increment;
		x++;
	}
	// BONUS
//	draw_minimap(info->image, info->map, info);
/*	if (mlx_image_to_window(info->mlx, info->image, 0, 0) < 0)
	{
		ft_putstr_fd("could not put image to window\nexiting..", 2);
		mlx_close_window(info->mlx);
		exit(1);
	i}*/

}

void	keyboard_movements(mlx_t *mlx, t_raycasting *info)
{
	t_point			tmp;

	tmp.x = info->player.x;
	tmp.y = info->player.y;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		tmp.y -= 0.20 * sin(degree_to_radian(info->direction));
		// restamos porque cuando los rayos miran abajo, sin es negativo y como queremos avanzar, la y será positiva
		tmp.x += 0.20 * cos(degree_to_radian(info->direction));
		// tenemos que sumar en player.x porque el resultado de cos puede ser negativo(cuando rayo mira a la izquierda) o positivo
		if (/*!is_wall(tmp.x, tmp.y, info->map) || */safe_point2(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
		//	printf("KEY after: player x = %f, y = %f\n\n", info->player.x, info->player.y);
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		tmp.y += 0.20 * sin(degree_to_radian(info->direction));
		tmp.x -= 0.20 * cos(degree_to_radian(info->direction));
		if (/*!is_wall(tmp.x, tmp.y, info->map) ||*/ safe_point2(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		tmp.x -= 0.20 * sin(degree_to_radian(info->direction));
		tmp.y -= 0.20 * cos(degree_to_radian(info->direction));
		if (/*!is_wall(tmp.x, tmp.y, info->map) ||*/ safe_point2(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		tmp.x += 0.20 * sin(degree_to_radian(info->direction));
		tmp.y += 0.20 * cos(degree_to_radian(info->direction));
		if (/*!is_wall(tmp.x, tmp.y, info->map) || */safe_point2(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}
	}
}

void	player_movements(void *param)
{
	t_raycasting	*info;
	
	info = (t_raycasting *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(info->mlx, info->image);
		mlx_close_window(info->mlx);
		exit(0);
	}
	// ROTACIÓN FOV (flechitas)
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->direction += 5;
		print_scene(info, info->map, info->ray);
	}	
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 5;
		print_scene(info, info->map, info->ray);
	}
	keyboard_movements(info->mlx, info);
}

/*void	keyboard_input(mlx_key_data_t keydata, void *param)
{
	(void)keydata;
	mlx_t			*mlx;
	t_raycasting	*info;
	
	info = (t_raycasting *)param;
	mlx = (mlx_t *)info->mlx;
//	printf("KEY\nplayer x = %f, y = %f\n\n", info->player.x, info->player.y);
//	printf("key = %d\n", keydata.key);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(mlx, info->image);
		mlx_close_window(mlx);
		exit(0);
	}
	// ROTACIÓN FOV (flechitas)
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		info->direction += 5;
		print_scene(info, info->map, info->ray);
	}	
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 5;
		print_scene(info, info->map, info->ray);
	}	
	keyboard_movements(mlx, info);
}*/

void	free_game(t_raycasting *game)
{
	mlx_delete_image(game->mlx, game->image);
    mlx_terminate(game->mlx);
	free(game->ray);
	free(game);
}

/*int	main(int argc, char **argv)
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
}*/
