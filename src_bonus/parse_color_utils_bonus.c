/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:28:53 by crmanzan          #+#    #+#             */
/*   Updated: 2025/03/08 17:28:57 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d_bonus.h"

static int	parse_number(char **trimmed, int *color, int *i)
{
	int	num;

	num = 0;
	while (ft_isspace(**trimmed))
		(*trimmed)++;
	if (!ft_isdigit(**trimmed))
		return (printf("\033[31mError:\nInvalid color format \
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

int	parse_color_values(char **current, int *color)
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
		return (printf("\033[31mError:\nInvalid color format.\n\033[0m"), 0);
	return (1);
}
