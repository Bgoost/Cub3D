/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:16:00 by crmanzan          #+#    #+#             */
/*   Updated: 2025/02/13 19:25:37 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	validate_and_assign_texture_path(const char *result,
	char **destination)
{
	if (*destination != NULL)
		exit_error("Error:\nDuplicate texture identifier.");
	*destination = ft_strdup(result);
	if (*destination == NULL)
		exit_error("Error:\nMemory allocation failed for texture path.");
}

static void	parse_texture(char *line, const char *identifier,
			char **destination)
{
	int		is_in_quotes;
	char	*trimmed;
	char	result[MAX_LINE_LEN];

	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
	is_in_quotes = extract_texture_path(trimmed, result);
	free(trimmed);
	if (is_in_quotes)
		exit_error("Error:\nUnmatched quotes in texture path.");
	validate_and_assign_texture_path(result, destination);
}

static void	parse_number_and_comma(char **trimmed, int *color,
			int *i, int *comma_count)
{
	int	num;

	while (ft_isspace(**trimmed))
		(*trimmed)++;
	if (ft_isdigit(**trimmed))
	{
		num = 0;
		while (ft_isdigit(**trimmed))
			num = num * 10 + (*(*trimmed)++ - '0');
		if (num > 255 || num < 0)
			exit_error("Error:\nColor values must be in range [0,255].");
		color[(*i)++] = num;
		while (ft_isspace(**trimmed))
			(*trimmed)++;
		if (**trimmed == ',')
		{
			(*comma_count)++;
			(*trimmed)++;
		}
		else if (**trimmed != '\0' && *i < 3)
			exit_error("Error:\nInvalid color format (missing commas).");
	}
	else
		exit_error("Error:\nInvalid color format (non-digit character found).");
}

static void	parse_color(char *line, const char *identifier, int *color)
{
	char	*trimmed;
	char	*current;
	int		i;
	int		comma_count;

	i = 0;
	comma_count = 0;
	if (color[i] != -1)
		exit_error("Error:\nDuplicate color identifier.");
	trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
	current = trimmed;
	while (*current != '\0' && i < 3)
	{
		parse_number_and_comma(&current, color, &i, &comma_count);
	}
	if ((*current != '\0' && !ft_isspace(*current))
		|| i != 3 || comma_count != 2)
	{
		free(trimmed);
		exit_error("Error:\nInvalid color format.");
	}
	free(trimmed);
}

void	parse_main_textures(char *line, t_map *scene, int map_started)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (*trimmed == '\0')
	{
		free(trimmed);
		return ;
	}
	if (ft_strncmp_isspace(trimmed, "NO"))
		parse_texture(trimmed, "NO", &scene->textures.north);
	else if (ft_strncmp_isspace(trimmed, "SO"))
		parse_texture(trimmed, "SO", &scene->textures.south);
	else if (ft_strncmp_isspace(trimmed, "WE"))
		parse_texture(trimmed, "WE", &scene->textures.west);
	else if (ft_strncmp_isspace(trimmed, "EA"))
		parse_texture(trimmed, "EA", &scene->textures.east);
	else if (ft_strncmp_isspace(trimmed, "F"))
		parse_color(trimmed, "F", scene->textures.floor_color);
	else if (ft_strncmp_isspace(trimmed, "C"))
		parse_color(trimmed, "C", scene->textures.ceiling_color);
	else if (!is_strspace(trimmed) && !map_started)
		error_invalid_identifier(trimmed);
	free(trimmed);
}
