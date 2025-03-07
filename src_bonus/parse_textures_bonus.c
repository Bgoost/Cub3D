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

#include "../inc/cub3d_bonus.h"

static void	validate_and_assign_texture_path(char *line, const char *result,
	char **destination, t_map *scene)
{
	if (*destination != NULL)
	{
		free(line);
		free_scene(&scene);
		exit_error("Error:\nDuplicate texture identifier.");
	}
	*destination = ft_strdup(result);
	if (*destination == NULL)
	{
		free(line);
		free_scene(&scene);
		exit_error("Error:\nMemory allocation failed for texture path.");
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
		exit_error("Error:\nUnmatched quotes in texture path.");
	validate_and_assign_texture_path(line, result, destination, scene);
}

static int	parse_number(char **trimmed, int *color, int *i)
{
	int	num;

	num = 0;
	while (ft_isspace(**trimmed))
		(*trimmed)++;
	if (!ft_isdigit(**trimmed))
		return (printf("\033[31mError:\nInvalid color format\
(non-digit character found).\n\033[0m"), 0);
	while (ft_isdigit(**trimmed))
		num = num * 10 + (*(*trimmed)++ - '0');
	if (num > 255 || num < 0)
		return (printf("\033[31mError:\nColor values must be\
in range [0,255].\n\033[0m"), 0);
	color[(*i)++] = num;
	return (1);
}

static int	parse_comma(char **trimmed, int *comma_count, int i)
{
	while (ft_isspace(**trimmed))
		(*trimmed)++;
	if (**trimmed == ',')
	{
		(*comma_count)++;
		(*trimmed)++;
	}
	else if (**trimmed != '\0' && i < 3)
		return (printf("\033[31mError:\nInvalid color format\
(missing commas).\n\033[0m"), 0);
	return (1);
}

static int	parse_number_and_comma(char **trimmed, int *color, int *i,
				int *comma_count)
{
	if (!parse_number(trimmed, color, i))
		return (0);
	return (parse_comma(trimmed, comma_count, *i));
}

// static void	parse_color(char *line, const char *identifier,
//		int *color, t_map *scene)
// {
//	char	*trimmed;
//	char	*current;
//	int		i;
//	int		comma_count;

//	i = 0;
//	comma_count = 0;
//	if (color[i] != -1)
//		exit_error("Error:\nDuplicate color identifier.");
//	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
//	current = trimmed;
//	while (*current != '\0' && i < 3)
//	{
//		if (parse_number_and_comma(&current, color, &i, &comma_count) == 0)
//		{
//			free(line);
//			free(trimmed);
//			free_scene(&scene);
//			exit(1);
//		}
//	}
//	if ((*current != '\0' && !ft_isspace(*current))
//		|| i != 3 || comma_count != 2)
//	{
//		free(line);
//		free(trimmed);
//		exit_error("Error:\nInvalid color format.");
//	}
//	free(trimmed);
// }

static char	*trim_color_line(char *line, const char *identifier)
{
	char	*trimmed;

	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
	if (!trimmed)
		exit_error("Error:\nMemory allocation failed while trimming.");
	return (trimmed);
}

static int	parse_color_values(char **current, int *color)
{
	int	i;
	int	comma_count;

	comma_count = 0;
	i = 0;
	while (**current != '\0' && i < 3)
	{
		if (!parse_number_and_comma(current, color, &i, &comma_count))
			return (0);
	}
	if ((**current != '\0' && !ft_isspace(**current)) || i != 3
		|| comma_count != 2)
		return (0);
	return (1);
}

static void	parse_color(char *line, const char *identifier,
			int *color, t_map *scene)
{
	char	*trimmed;
	char	*current;

	if (color[0] != -1)
		exit_error("Error:\nDuplicate color identifier.");
	current = trimmed;
	trimmed = trim_color_line(line, identifier);
	if (!parse_color_values(&current, color))
	{
		free(line);
		free(trimmed);
		exit_error("Error:\nInvalid color format.");
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
