/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:08:14 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/11 20:04:40 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*sfin;
	int		i;
	int		n;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	sfin = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = -1;
	n = 0;
	if (!sfin)
		return (free_all_gnl(&s1));
	while (s1[++i] != '\0')
	{
		sfin[i] = s1[i];
	}
	while (s2[n] != '\0')
		sfin[i++] = s2[n++];
	sfin[i] = '\0';
	free(s1);
	return (sfin);
}

char	*ft_substr_gnl(const char *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	size;
	size_t	i;

	if (!s || len == 0)
		return (NULL);
	size = 0;
	while (s[size])
		size++;
	if (start >= size)
		return (NULL);
	if (len > size - start)
		s2 = (char *)malloc((size - start + 1) * sizeof(char));
	else
		s2 = (char *)malloc((len + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	len += start;
	i = 0;
	while (s[start] && start < len)
		s2[i++] = s[start++];
	s2[i] = '\0';
	return (s2);
}
