/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:29:10 by crmanzan          #+#    #+#             */
/*   Updated: 2025/03/08 21:17:00 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

static char	*allocate_padded_line(char *trimmed, t_map *scene, char **copy_map)
{
	char	*padded_line;

	padded_line = pad_line_to_width(trimmed, scene->width);
	if (!padded_line)
	{
		free_map(copy_map);
		free_map(scene->map);
		exit_error("Error:\nMemory allocation for padded line failed.\n");
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
		exit_error("Error:\nMemory allocation for map line failed.\n");
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
		exit_error("Error:\nMemory allocation for trimmed line failed.\n");
	padded_line = allocate_padded_line(trimmed, scene, copy_map);
	assign_map_lines(scene, i, padded_line, copy_map);
	free(trimmed);
	process_map_chars(scene, i, num_players, copy_map);
}
