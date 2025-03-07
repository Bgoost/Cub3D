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

// void	process_line(t_map *scene, int i, int *num_players, char **copy_map)
// {
//	int		j;
//	char	*trimmed;
//	char	*padded_line;

//	j = 0;
//	trimmed = ft_strtrim(scene->lines[i], "\n");
//	if (!trimmed)
//		exit_error("Error:\nMemory allocation for trimmed line failed.");
//	padded_line = pad_line_to_width(trimmed, scene->width);
//	if (!padded_line)
//	{
//		free_map(copy_map);
//		free_map(scene->map);
//		exit_error("Error:\nMemory allocation for padded line failed.");
//	}
//	if (scene->map[i - scene->start])
//		free(scene->map[i - scene->start]);
//	if (copy_map[i - scene->start])
//		free(copy_map[i - scene->start]);
//	scene->map[i - scene->start] = padded_line;
//	copy_map[i - scene->start] = pad_line_to_width(trimmed, scene->width);
//	free(trimmed);
//	if (!scene->map[i - scene->start] || !copy_map[i - scene->start])
//		exit_error("Error:\nMemory allocation for map line failed.");
//	while (scene->lines[i][j] != '\0')
//	{
//		if (!set_map_chars(scene, i, j, num_players))
//		{
//			free_map(copy_map);
//			exit(1);
//		}
//		j++;
//	}
// }

static char	*allocate_padded_line(char *trimmed, t_map *scene, char **copy_map)
{
	char	*padded_line;

	padded_line = pad_line_to_width(trimmed, scene->width);
	if (!padded_line)
	{
		free_map(copy_map);
		free_map(scene->map);
		exit_error("Error:\nMemory allocation for padded line failed.");
	}
	return (padded_line);
}

static void	assign_map_lines(t_map *scene, int i, char *padded_line,
				char **copy_map)
{
	int	index;

	index = i - scene->start;
	if (scene->map[index])
		free(scene->map[index]);
	if (copy_map[index])
		free(copy_map[index]);
	scene->map[index] = padded_line;
	copy_map[index] = pad_line_to_width(padded_line, scene->width);
	if (!scene->map[index] || !copy_map[index])
		exit_error("Error:\nMemory allocation for map line failed.");
}

static void	process_map_chars(t_map *scene, int i, int *num_players,
				char **copy_map)
{
	int	j;

	j = 0;
	while (scene->lines[i][j] != '\0')
	{
		if (!set_map_chars(scene, i, j, num_players))
		{
			free_map(copy_map);
			exit(1);
		}
		j++;
	}
}

void	process_line(t_map *scene, int i, int *num_players, char **copy_map)
{
	char	*trimmed;
	char	*padded_line;

	trimmed = ft_strtrim(scene->lines[i], "\n");
	if (!trimmed)
		exit_error("Error:\nMemory allocation for trimmed line failed.");
	padded_line = allocate_padded_line(trimmed, scene, copy_map);
	assign_map_lines(scene, i, padded_line, copy_map);
	free(trimmed);
	process_map_chars(scene, i, num_players, copy_map);
}

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
		exit_error("Error:\nMap is not fully surrounded by walls.");
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
		exit_error("Error:\nMemory allocation for map failed.");
	copy_map = init_allocate_map(scene->height, scene->width);
	if (!copy_map)
	{
		free_map(scene->map);
		exit_error("Error:\nMemory allocation for map failed.");
	}
	while (i <= scene->end)
	{
		process_line(scene, i, &num_players, copy_map);
		i++;
	}
	validate_and_clean_map(scene, copy_map, num_players);
}
