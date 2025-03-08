/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parse_textures_bonus.c								:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/02/13 19:16:00 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/03/07 22:57:52 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	validate_and_assign_texture_path(char *line, const char *result,
	char **destination, t_map *scene)
{
	if (*destination != NULL)
	{
		free(line);
		free_scene(&scene);
		exit_error("Error:\nDuplicate texture identifier.\n");
	}
	*destination = ft_strdup(result);
	if (*destination == NULL)
	{
		free(line);
		free_scene(&scene);
		exit_error("Error:\nMemory allocation failed for texture path.\n");
	}
}

static void	parse_texture(char *line, const char *identifier,
			char **destination, t_map *scene)
{
	int		is_in_quotes;
	char	*trimmed;
	char	result[MAX_LINE_LEN];

	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
	is_in_quotes = extract_texture_path(trimmed, result);
	free(trimmed);
	if (is_in_quotes)
		exit_error("Error:\nUnmatched quotes in texture path.\n");
	validate_and_assign_texture_path(line, result, destination, scene);
}

static char	*trim_color_line(char *line, const char *identifier)
{
	char	*trimmed;

	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
	if (!trimmed)
		exit_error("Error:\nMemory allocation failed while trimming.\n");
	return (trimmed);
}

static void	parse_color(char *line, const char *identifier,
			int *color, t_map *scene)
{
	char	*trimmed;
	char	*current;

	if (color[0] != -1)
	{
		free(line);
		free_scene(&scene);
		exit_error("Error:\nDuplicate color identifier.\n");
	}
	trimmed = trim_color_line(line, identifier);
	current = trimmed;
	if (!parse_color_values(&current, color))
	{
		free(line);
		free(trimmed);
		free_scene(&scene);
		exit_error("");
	}
	free(trimmed);
}

void	parse_main_textures(char *line, t_map *scene, int map_started)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
	{
		free_scene(&scene);
		free(trimmed);
		return ;
	}
	if (ft_strncmp_isspace(trimmed, "NO"))
		parse_texture(trimmed, "NO", &scene->textures.north, scene);
	else if (ft_strncmp_isspace(trimmed, "SO"))
		parse_texture(trimmed, "SO", &scene->textures.south, scene);
	else if (ft_strncmp_isspace(trimmed, "WE"))
		parse_texture(trimmed, "WE", &scene->textures.west, scene);
	else if (ft_strncmp_isspace(trimmed, "EA"))
		parse_texture(trimmed, "EA", &scene->textures.east, scene);
	else if (ft_strncmp_isspace(trimmed, "F"))
		parse_color(trimmed, "F", scene->textures.floor_color, scene);
	else if (ft_strncmp_isspace(trimmed, "C"))
		parse_color(trimmed, "C", scene->textures.ceiling_color, scene);
	else if (!is_strspace(trimmed) && !map_started)
		error_invalid_identifier(trimmed, scene);
	free(trimmed);
}
