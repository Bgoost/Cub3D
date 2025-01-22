/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 14:00:15 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/26 13:56:23 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	word_count(const char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			words++;
		i++;
	}
	return (words);
}

void	free_words(char	**words)
{
	size_t	i;

	i = 0;
	if (!words)
		return ;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	words = 0;
}

char	**copy_words(char const *s, char c, char **words, size_t word_count)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	start = 0;
	while (i < word_count)
	{
		while (s[j] == c)
			j++;
		start = j;
		while (s[j] && s[j] != c)
			j++;
		words[i] = ft_substr(s, start, j - start);
		if (!words[i])
		{
			free_words(words);
			words = NULL;
			return (0);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}

char	**ft_split(char const *s, char c)
{
	size_t	word;
	char	**split;

	if (!s)
		return (0);
	word = word_count(s, c);
	split = malloc((word + 1) * sizeof(char *));
	if (!split)
		return (0);
	split = copy_words(s, c, split, word);
	return (split);
}
/*
#include <stdio.h>
int main()
{
	char **split;
	char *str = "Hola buenas tardes como estammos";
	char c = ' ';
	int i;

	split = ft_split(str, c);

	while (split[i])
	{
		printf("%s\n", split[i++]);
	}

}*/
