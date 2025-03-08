/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_map.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/03/04 21:08:31 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/03/04 21:08:36 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../inc/cub3d_bonus.h"

static int	is_fully_enclosed(char **copy_map, t_map scene, int x, int y)
{
	int	right;
	int	left;
	int	down;
	int	up;

	if (x < 0 || x >= scene.width || y < 0 || y >= scene.height)
		return (0);
	if (copy_map[y][x] == '1' || copy_map[y][x] == 'F' || copy_map[y][x] == 'E')
		return (1);
	if (copy_map[y][x] == ' ')
		return (0);
	copy_map[y][x] = 'E';
	right = is_fully_enclosed(copy_map, scene, x + 1, y);
	left = is_fully_enclosed(copy_map, scene, x - 1, y);
	down = is_fully_enclosed(copy_map, scene, x, y + 1);
	up = is_fully_enclosed(copy_map, scene, x, y - 1);
	return (right && left && down && up);
}

int	is_valid_map(t_map *map, char **copy_map)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (copy_map[y][x] == '0')
			{
				if (!is_fully_enclosed(copy_map, *map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	map->valid_map = 1;
	return (1);
}

void	validate_and_clean_map(t_map *scene, char **copy_map, int num_players)
{
	int	is_valid;

	is_valid = is_valid_map(scene, copy_map);
	if (!is_valid || is_valid == -1)
	{
		free_map(copy_map);
		free_scene(&scene);
		exit_error("Error:\nMap is not fully surrounded by walls.\n");
	}
	free_map(copy_map);
	parse_map_errors(num_players, &scene);
}

void	parse_map(t_map *scene)
{
	char	**copy_map;
	int		num_players;
	int		i;

	scene->height = scene->end - scene->start + 1;
	num_players = 0;
	i = scene->start;
	scene->map = init_allocate_map(scene->height, scene->width);
	if (!scene->map)
		exit_error("Error:\nMemory allocation for map failed.\n");
	copy_map = init_allocate_map(scene->height, scene->width);
	if (!copy_map)
	{
		free_map(scene->map);
		exit_error("Error:\nMemory allocation for map failed.\n");
	}
	while (i <= scene->end)
	{
		process_line(scene, i, &num_players, copy_map);
		i++;
	}
	validate_and_clean_map(scene, copy_map, num_players);
}
