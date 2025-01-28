/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/01/27 20:53:08 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

#define MAP_HEIGHT 5
#define MAP_WIDTH 5

char	**hardcore_map(int height, int width, int fd)
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
			return (ft_putstr_fd("malloc error\n", 2), NULL);
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
	
	radian = (degree * PI) / 180.0;
	return (radian);
}

void	hardcore_info(t_raycasting *info)
{
	info->ray_increment = (double)FOV / (double)WIDTH;
	info->distance_to_plane = (WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	info->angle = 60;
	info->player.x = 1;
	info->player.y = 3;
	//printing info
	printf("\nFOV: %d\n", FOV);
	printf("WINDOW HEIGHT: %d\n", HEIGHT);
	printf("WINDOW WIDTH: %d\n", WIDTH);
	printf("\nray increment: %f\n", info->ray_increment);
	printf("distance_to_plane: %f\n", info->distance_to_plane);
	printf("player angle: %f\n", info->angle);
	printf("player X: %f\n", info->player.x);
	printf("player Y: %f\n\n", info->player.y);
}


t_point	horizontal_hit(t_raycasting info, char **map)
{
	t_point	grid_player;
	t_point	hit;
	double	x_increment;
	double	y_increment;

	printf("HORIZONTAL HITS\n");	

	// pasamos de 1 x 1 a 64 x 64 y ponemos el punto en el medio
	grid_player.x = info.player.x * TILE + TILE / 2;
	grid_player.y = info.player.y * TILE + TILE / 2;

	// 1. first point
	hit.y = floor(grid_player.y / TILE) * TILE - 1; 
	hit.x = grid_player.x + (grid_player.y - hit.y) / tan(degree_to_radian(info.angle));
	printf("1st hit: P(%f, %f)\n", hit.x, hit.y);
	printf("scaled down: P(%d, %d)\n", (int)hit.x / TILE, (int)hit.y / TILE);

	if (map[(int)hit.y / TILE][(int)hit.x / TILE] == '1')
		return (printf("theres a wall in first point\n"), hit);

	// 2. Remaining points
	// 2.1. Find y_increment & x_increment
	if (info.angle >= 0 && info.angle <= 180) // if ray looks UP 
		y_increment = -TILE;
	else
		y_increment = TILE;
	x_increment = floor(TILE / tan(degree_to_radian(info.angle)));
	
	x_increment = floor(x_increment); // DUDA
	printf("x_increment = %f\ny_increment = %f\n\n", x_increment, y_increment);	
	
	while (map[(int)hit.y / TILE][(int)hit.x /TILE] == '0') 
	{
		// 2.2. Add increments to find next point
		hit.x = hit.x + x_increment;
		hit.y = hit.y + y_increment;

		hit.x = floor(hit.x); // DUDA
		hit.y = floor(hit.y); // DUDA

		printf("next hit: (%f, %f)\n", hit.x, hit.y);
		printf("scaled down: (%d, %d)\n\n", (int)hit.x / TILE, (int)hit.y / TILE);
	}
	return (hit);
}

t_point	vertical_hit(t_raycasting info, char **map)
{
	t_point	grid_player;
	t_point	hit;
	double	x_increment;
	double	y_increment;

	printf("VERTICAL HITS\n");	

	// pasamos de 1 x 1 a 64 x 64 y ponemos el punto en el medio
	grid_player.x = info.player.x * TILE + TILE / 2;
	grid_player.y = info.player.y * TILE + TILE / 2;

		// 1. first point
	if (info.angle <= 270 && info.angle >= 90) // if angle looks left  ??
		hit.x = floor(grid_player.x / TILE) * TILE - 1;
	else
		hit.x = floor(grid_player.x / TILE) * TILE + TILE;
	hit.y = grid_player.y + (grid_player.x - hit.x) * tan(degree_to_radian(info.angle));
	printf("1st hit: P(%f, %f)\n", hit.x, hit.y);
	printf("scaled down: P(%d, %d)\n", (int)hit.x / TILE, (int)hit.y / TILE);

	if (map[(int)hit.y / TILE][(int)hit.x / TILE] == '1')
		return (printf("theres a wall in first point\n"), hit);

	// 2. Remaining points
	// 2.1. Find y_increment & x_increment
	if (info.angle <= 270 && info.angle >= 90) // if angle looks left  ??
		x_increment = -TILE;
	else
		x_increment = TILE;
	y_increment = x_increment * tan(degree_to_radian(info.angle));
	y_increment = floor(y_increment); // DUDA
	printf("x_increment = %f\ny_increment = %f\n\n", x_increment, y_increment);	
	
	while (map[(int)hit.y / TILE][(int)hit.x /TILE] == '0')
	{
		// 2.2. Add increments to find next point
		hit.x = hit.x + x_increment;
		hit.y = hit.y - y_increment; // !!! resta
		
		hit.x = floor(hit.x); // DUDA
		hit.y = floor(hit.y); // DUDA

		printf("next hit: (%f, %f)\n", hit.x, hit.y);
		printf("scaled down: (%d, %d)\n\n", (int)hit.x / TILE, (int)hit.y / TILE);
	}
	return (hit);
}

double	point_distance(t_point hit, t_point player)
{
	double	distance;
	
	player.x = player.x * TILE + TILE / 2;
	player.y = player.y * TILE + TILE / 2;

	distance = sqrt(pow((player.x - hit.x), 2) + pow((player.y - hit.y), 2));
	printf("\ndistance: %f\n", distance);
	return (distance);
}


t_ray	*cast_ray(t_raycasting info, char **map)
{
	t_ray	*ray;
	t_point	v_hit;
	t_point	h_hit;
	double	v_distance;
	double	h_distance;

	ray = malloc(sizeof(t_ray) * 1);
	if (!ray)
		return (ft_putstr_fd("malloc error\n", 2), NULL);

	// HORIZONTAL intersections
	h_hit = horizontal_hit(info, map);

	// VERTICAL intersections
	v_hit = vertical_hit(info, map);

	// calculating DISTANCE
   	// find distance from player to each hit point (vertical & horizontal)
	v_distance = point_distance(v_hit, info.player);
	h_distance = point_distance(h_hit, info.player);

	// save shortest distance & point
	if (v_distance < h_distance)
	{
		ray->distance_to_wall = v_distance;
		ray->hit_point = v_hit;
	}
	else
	{
		ray->distance_to_wall = h_distance;
		ray->hit_point = h_hit;
	}
	printf("\nfinal distance to wall: %f\n", ray->distance_to_wall);
	printf("final hit point: (%f, %f)\n", ray->hit_point.x, ray->hit_point.y);
	printf("scaled down: (%d, %d)\n\n", (int)ray->hit_point.x / TILE, (int)ray->hit_point.y / TILE);

	// Find projected wall height

	// Real wall height = TILE
	// Distance to plane = (WIDTH/2)/tan(FOV/2)
	
   // FORMULA
   // Projected Wall Height = (real wall height / distance to wall) * distance to projection plane
   // PWH = (TILE / ray->distance_to_wall) * ray->distance_to_plane;

	ray->projection_height = (TILE / ray->distance_to_wall) * info.distance_to_plane;
	ray->projection_height = ceil(ray->projection_height); // round UP 

	// need to do another function to check this value is correct		

	// Find first wall point
	// t_point	center;

	// center.x = WIDTH / 2;
	// center.y = HEIGHT / 2;

	// Find last wall point
	
	// PRINT PIXELS
	// print pixels from y = 0 to the first wall point as ceiling color
	// print pixels from first wall point to last wall point as wall color (later textures)
	// print pixels from last wall point to end of screen (y = 1000) as ground color

	return (ray);
}

// funciona con el maps/test_map.cub

/*int	main(int argc, char **argv)
{
	(void)argc;
	int	fd;
	t_raycasting	info;
	char	**map;
	t_ray 	*ray;

	fd = -1;
	fd = open(argv[1], O_RDWR);
	if (fd == -1)
		ft_putstr_fd("failed to open file\n", 2);
	map = hardcore_map(MAP_HEIGHT, MAP_WIDTH, fd);
	hardcore_info(&info);
	ray = cast_ray(info, map);
//	loop to increment angle until we reach inital angle + 60	
//	angle = ray->angle + info.ray_increment;
	return (0);
}
*/
