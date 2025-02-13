/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:16:00 by crmanzan          #+#    #+#             */
/*   Updated: 2025/02/13 19:24:39 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	extract_texture_path(const char *trimmed, char *result)
{
	int	i;
	int	in_quotes;
	int	result_len;

	i = 0;
	in_quotes = 0;
	result_len = 0;
	ft_bzero(result, MAX_LINE_LEN);
	while (trimmed[i] != '\0')
	{
		if (trimmed[i] == '"')
			in_quotes = !in_quotes;
		else if (in_quotes || !ft_isspace(trimmed[i]))
		{
			if (result_len < MAX_LINE_LEN - 1)
				result[result_len++] = trimmed[i];
			else
				exit_error("Error:\nTexture path is too long.");
		}
		else
			exit_error("Error:\nFound a space in the file.");
		i++;
	}
	result[result_len] = '\0';
	return (in_quotes);
}

void	error_invalid_identifier(char *trimmed)
{
	char	**split_error;

	split_error = ft_split(trimmed, ' ');
	if (split_error == NULL)
		exit_error("Error:\nMemory allocation failed for split error.");
	printf("\033[31mError:\nInvalid texture identifier [%s]i \
					in file.\n\033[0m", split_error[0]);
	printf("\033[31mExpected identifiers: NO, SO, WE, EA, F, C\033[0m");
	free(trimmed);
	exit_error("");
}
