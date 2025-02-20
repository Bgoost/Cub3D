/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_360.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/02/07 16:05:36 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MAP_HEIGHT 22
#define MAP_WIDTH 21

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
}

double	degree_to_radian(double degree)
{
	double	radian;
	
	radian = (degree * M_PI) / (double)180.0;
	return (radian);
}

void	hardcode_info(t_game *info)
{
	info->ray_increment = (double)FOV / (double)WIDTH;
	info->distance_to_plane = (WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	info->direction = 0;
	info->player.x = 6;
	info->player.y = 17;
	//printing info
	printf("\nFOV: %d\n", FOV);
	printf("WINDOW HEIGHT: %d\n", HEIGHT);
	printf("WINDOW WIDTH: %d\n", WIDTH);
	printf("\nray increment: %f\n", info->ray_increment);
	printf("distance_to_plane: %f\n", info->distance_to_plane);
	printf("player direction: %f\n", info->direction);
	printf("player X: %f\n", info->player.x);
	printf("player Y: %f\n\n", info->player.y);
}


t_point	*horizontal_hit(t_point player, char **map, double angle)
{
	t_point	grid_player;
	t_point	*hit;
	t_point	*max_hit;
	double	x_increment;
	double	y_increment;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	max_hit = malloc(sizeof(t_point) * 1);
	if (!max_hit)
		return (NULL);
	max_hit->x = DOUBLE_MAX;
	max_hit->y = DOUBLE_MAX;

//	printf("HORIZONTAL HITS\n");	

	// pasamos de 1 x 1 a 64 x 64 y ponemos el punto en el medio
	grid_player.x = player.x * TILE + TILE / 2;
	grid_player.y = player.y * TILE + TILE / 2;
//	printf("plaxer: P(%f, %f)\n", grid_player.x, grid_player.y);
//	printf("scaled down: P(%d, %d)\n", (int)grid_player.x / TILE, (int)grid_player.y / TILE);

	// 1. first point
	if (angle <= 180 && angle >= 0)
		hit->y = floor(grid_player.y / TILE) * TILE - 0.000000000001; 
	else
		hit->y = floor(grid_player.y / TILE) * TILE + TILE; 
	hit->x = grid_player.x + (grid_player.y - hit->y) / tan(degree_to_radian(angle));
	
//	printf("1st hit: P(%f, %f)\n", hit->x, hit->y);
//	printf("scaled down: P(%d, %d)\n", (int)hit->x / TILE, (int)hit->y / TILE);

	if ((int)hit->x / TILE < 0 || ((int)hit->x / TILE) >= MAP_WIDTH)
	{
	//	printf("x out of bounds in first hit\n");
		return (hit);
	}
	if ((int)hit->y / TILE < 0 || ((int)hit->y / TILE) >= MAP_HEIGHT)
	{
	//	printf("y out of bounds in first hit\n");
		return (hit);
	}
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
	{
	//	printf("theres a wall in first point\n");
		return (hit);
	}

	// 2. Remaining points
	// 2.1. Find y_increment & x_increment
	if (angle >= 0 && angle <= 180) // if ray looks UP 
		y_increment = -TILE;
	else
		y_increment = TILE;
	if (angle >= 90 && angle <= 270)
		x_increment = -fabs(TILE / tan(degree_to_radian(angle)));
	else
		x_increment = fabs(TILE / tan(degree_to_radian(angle)));
	
//	x_increment = TILE / tan(degree_to_radian(angle));

//	printf("x_increment = %f\ny_increment = %f\n\n", x_increment, y_increment);	
	
	while (map[(int)hit->y / TILE][(int)hit->x / TILE] == '0') 
	{
		// 2.2. Add increments to find next point
		hit->x = hit->x + x_increment;
		hit->y = hit->y + y_increment;

//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);

		if ((int)hit->y / TILE < 0 || ((int)hit->y / TILE) >= MAP_HEIGHT)
		{
//			printf("y is out of bounds\n");
			return (hit);
		}
		if ((int)hit->x / TILE < 0 || ((int)hit->x / TILE) >= MAP_WIDTH)
		{
//			printf("x is out of bounds\n");
			return (hit);
		}
	}
	return (hit);
}

t_point	*vertical_hit(t_point player, char **map, double angle)
{
	t_point	grid_player;
	t_point	*hit;
	t_point	*max_hit;
	double	x_increment;
	double	y_increment;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	max_hit = malloc(sizeof(t_point) * 1);
	if (!max_hit)
		return (NULL);

	max_hit->x = DOUBLE_MAX;
	max_hit->y = DOUBLE_MAX;

//	printf("VERTICAL HITS\n");	

	// pasamos de 1 x 1 a 64 x 64 y ponemos el punto en el medio
	grid_player.x = player.x * TILE + TILE / 2;
	grid_player.y = player.y * TILE + TILE / 2;

		// 1-> first point
	if (angle <= 270 && angle >= 90) // if angle looks left  ??
		hit->x = floor(grid_player.x / TILE) * TILE - 0.000000000001; 
	else
		hit->x = floor(grid_player.x / TILE) * TILE + TILE;
	hit->y = grid_player.y + (grid_player.x - hit->x) * tan(degree_to_radian(angle));

//	printf("1st hit: P(%f, %f)\n", hit->x, hit->y);
//	printf("scaled down: P(%d, %d)\n", (int)hit->x / TILE, (int)hit->y / TILE);
	
	if ((int)hit->y / TILE < 0 || ((int)hit->y / TILE) >= MAP_HEIGHT)
	{
	//	printf("y out of bounds in first hit\n");
		return (hit);
	}
	if ((int)hit->x / TILE < 0 || ((int)hit->x / TILE) >= MAP_WIDTH)
	{
	//	printf("x out of bounds in first hit\n");
		return (hit);
	}

	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
	{
	//	printf("theres a wall in first point\n");
		return (hit);
	}

	// 2. Remaining points
	// 2.1. Find y_increment & x_increment
	if (angle <= 270 && angle >= 90) // if angle looks left  ??
		x_increment = -TILE;
	else
		x_increment = TILE;

	if (angle <= 180 && angle >= 0)
		y_increment = -fabs(TILE * tan(degree_to_radian(angle)));
	else
		y_increment = fabs(TILE * tan(degree_to_radian(angle)));
//	y_increment = TILE * tan(degree_to_radian(angle));
//	printf("x_increment = %f\ny_increment = %f\n\n", x_increment, y_increment);	
	
	while (map[((int)hit->y / TILE)][(int)hit->x / TILE] == '0')
	{
		// 2.2. Add increments to find next point
		hit->x = hit->x + x_increment;
		hit->y = hit->y + y_increment; // !!! antes tenia resta
		
//		printf("next hit: (%f, %f)\n", hit->x, hit->y);
//		printf("scaled down: (%d, %d)\n\n", (int)hit->x / TILE, (int)hit->y / TILE);
		
		if ((int)hit->y / TILE < 0 || ((int)hit->y / TILE) >= MAP_HEIGHT)
		{
		//	printf("y is out of bounds\n");
			return (hit);
		}
		if ((int)hit->x / TILE < 0 || ((int)hit->x / TILE) >= MAP_WIDTH)
		{
	//		printf("x is out of bounds\n");
			return (hit);
		}
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


void	cast_ray(t_game info, char **map, t_ray *ray)
{
	t_point	*v_hit;
	t_point	*h_hit;
	double	v_distance;
	double	h_distance;


//	printf("\n\nANGLE %f\n-------------------------\n", ray->angle);
//	printf("direction: %f\n", info.direction);
	// HORIZONTAL intersections
	h_hit = horizontal_hit(info.player, map, ray->angle);
//	printf("h hit: (%f, %f)\n", h_hit->x, h_hit->y);
//	printf("scaled down: (%d, %d)\n\n", (int)(h_hit->x / TILE), (int)(h_hit->y / TILE));

	// VERTICAL intersections
	v_hit = vertical_hit(info.player, map, ray->angle);
//	printf("v hit: (%f, %f)\n", v_hit->x, v_hit->y);
//	printf("scaled down: (%d, %d)\n\n", (int)(v_hit->x / TILE), (int)(v_hit->y / TILE));
	
	// calculating DISTANCE
//	printf("DISTANCE\n");	
   	// find distance from player to each hit point (vertical & horizontal)
	if (v_hit->y < 0) //|| v_hit->y > MAP_HEIGHT * TILE)
		v_distance = DOUBLE_MAX;
	else
		v_distance = point_distance(*v_hit, info.player, 'v');
	
	if (h_hit->x < 0) // || h_hit->x > MAP_WIDTH * TILE)
		h_distance = DOUBLE_MAX;
	else
		h_distance = point_distance(*h_hit, info.player, 'h');

	// save shortest distance & point
	if (v_distance < h_distance)
	{
		ray->distance_to_wall = v_distance;
		ray->hit_point = *v_hit;
	}
	else
	{
		ray->distance_to_wall = h_distance;
		ray->hit_point = *h_hit;
	}
//	printf("\nfinal distance to wall: %f\n", ray->distance_to_wall);
//	printf("final hit point: (%f, %f)\n", ray->hit_point.x, ray->hit_point.y);
//	printf("scaled down: (%d, %d)\n", (int)ray->hit_point.x / TILE, (int)ray->hit_point.y / TILE);

	// OJO DE PEZ
//	printf("\nFISHEYE CORRECTION\n");	
	ray->distance_to_wall = ray->distance_to_wall * cos(degree_to_radian(ray->angle - info.direction));
//	printf("corrected distance to wall: %f\n", ray->distance_to_wall);


//	Find projected wall height

//	Real wall height = TILE
//	Distance to plane = (WIDTH/2)/tan(FOV/2)
	
  //  FORMULA
  //  Projected Wall Height = (real wall height / distance to wall) * distance to projection plane
  // 	PWH = (TILE / ray->distance_to_wall) * ray->distance_to_plane; 

	ray->projection_height = (TILE / ray->distance_to_wall) * info.distance_to_plane;
//	printf("\nprojection height: %f\n", ray->projection_height);

	// Function to check the value is correct		
//	printf("test.1: %f\n", ray->projection_height / info.distance_to_plane);
//	printf("test.2: %f\n", TILE / ray->distance_to_wall);
	if ((ray->projection_height / info.distance_to_plane) - (TILE / ray->distance_to_wall) > 0.00001)
	   printf("ERROR with projection heigth!\n");

	ray->projection_height = ceil(ray->projection_height); // round UP 
//	printf("\nprojection height rounded UP: %f\n", ray->projection_height);


	// Find first wall pixel
	t_point	center;

	center.x = WIDTH / 2;
	center.y = HEIGHT / 2;

	ray->first_wall_pixel = center.y - (ray->projection_height / 2);
//	printf("\nfirst_wall_pixel: %d\n", ray->first_wall_pixel);

	// Find last wall pixel
	ray->last_wall_pixel = ray->first_wall_pixel + ray->projection_height;
//	printf("last_wall_pixel: %d\n", ray->last_wall_pixel);
}

void	print_column(t_ray *ray, mlx_image_t *image, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT) // print column
	{
		if (y < ray->first_wall_pixel)
			mlx_put_pixel(image, x, y, CEILING_COLOR);
		else if (y >= ray->first_wall_pixel && y <= ray->last_wall_pixel)
			mlx_put_pixel(image, x, y, WALL_COLOR);
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

typedef struct s_game {
    mlx_t *mlx;
    mlx_image_t *image;
    t_game info;
    t_ray *ray;
    char **map;
    int direction_step;
} t_game;

void	render(void *param)
{
	t_game	*game = (t_game *)param;
	int	x;
	
	x = 0;
	for (int i = 0; i < WIDTH * HEIGHT; i++)
	{
		game->image->pixels[i] = 0x000000; // Black background
	}
	
	game->ray->angle = game->info.direction + (FOV / 2);
	game->ray->angle = adjust_angle(game->ray->angle);	


	while (x < WIDTH)
	{
		cast_ray(game->info, game->map, game->ray);
		print_column(game->ray, game->image, x);
		game->ray->angle = game->ray->angle - game->info.ray_increment;
		game->ray->angle = adjust_angle(game->ray->angle);	
		x++;
	}

	mlx_image_to_window(game->mlx, game->image, 0, 0);
	
	game->info.direction += 1;
	game->info.direction = adjust_angle(game->info.direction);
//	printf("direction = %f\n", game->info.direction);
	usleep(15000);
  //  if (game->info.direction >= 360.0) // Stop after a full rotation
    //    mlx_close_window(game->mlx); // Close the window and exit the loop
}

int	main(int argc, char **argv)
{
	(void)argc;
	int	fd;
	t_game	game;

	fd = -1;
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		return(ft_putstr_fd("failed to open file\n", 2), 1);
	game.map = hardcode_map(MAP_HEIGHT, MAP_WIDTH, fd);
	hardcode_info(&game.info);
	game.ray = malloc(sizeof(t_ray) * 1);
	if (!game.ray)
	{
		free_array(game.map);
		return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	game.ray->angle = game.info.direction + (FOV / 2);
	game.ray->angle = adjust_angle(game.ray->angle);	
	
	// PRINTING PIXELS
	game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!game.mlx)
		return (1);
	game.image = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
    mlx_terminate(game.mlx);
	return (0);
}*/
