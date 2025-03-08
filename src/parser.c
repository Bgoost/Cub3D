/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/03/04 21:10:30 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/03/04 21:10:30 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../inc/cub3d_bonus.h"

void	find_delimiter(char *line, int i, t_map *scene)
{
	int		width;
	char	*trimmed;

	trimmed = ft_strtrim(line, " \n");
	if (!is_strspace(line))
	{
		width = ft_strlen(trimmed);
		if (width > scene->width)
			scene->width = width;
		if (scene->start == 0)
			scene->start = i;
	}
	scene->end = i;
	scene->valid_map = 0;
	free(trimmed);
}

void	errors_in_map(t_map *scene)
{
	if (scene->start == 0)
	{
		free_scene(&scene);
		exit_error("Error:\nNo map found.\n");
	}
	if (!scene->textures.north || !scene->textures.south
		|| !scene->textures.west
		|| !scene->textures.east)
	{
		free_scene(&scene);
		exit_error("Error:\nMissing one or more textures.\n");
	}
	if (scene->textures.floor_color[0] == -1
		|| scene->textures.ceiling_color[0] == -1)
	{
		free_scene(&scene);
		exit_error("Error:\nMissing floor or ceiling color.\n");
	}
}

void	parse_scene_file(const char *filename, t_map *scene)
{
	int	lines_count;
	int	i;

	lines_count = get_lines_count(filename);
	set_file_lines(filename, scene, lines_count);
	i = 0;
	while (scene->lines[i] != NULL)
	{
		if (scene->textures.north && scene->textures.south
			&& scene->textures.west && scene->textures.east
			&& scene->textures.ceiling_color[0] != -1
			&& scene->textures.floor_color[0] != -1)
		{
			if (scene->valid_map == -1)
				parse_main_textures(scene->lines[i], scene, 1);
			find_delimiter(scene->lines[i], i, scene);
		}
		else
			parse_main_textures(scene->lines[i], scene, 0);
		i++;
	}
	errors_in_map(scene);
	parse_map(scene);
}
