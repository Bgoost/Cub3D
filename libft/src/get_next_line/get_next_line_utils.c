/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:16:12 by martalop          #+#    #+#             */
/*   Updated: 2024/08/13 14:59:06 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int	my_strchr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] != '\n')
		return (0);
	return (1);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub_s;

	i = (size_t) start;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen_gnl(s))
		len = 0;
	else if (len > ft_strlen_gnl(&s[i]))
		len = ft_strlen_gnl(&s[i]);
	sub_s = malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	while ((i < (start + len)) && (start < ft_strlen_gnl(s)))
		sub_s[j++] = s[i++];
	sub_s[j] = '\0';
	return (sub_s);
}

char	*free_strjoin(char *s1, char *s2)
{
	char	*strj;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	i = 0;
	j = 0;
	strj = malloc((sizeof(char)) * (s1_len + s2_len + 1));
	if (!strj)
		return (free(s1), NULL);
	while (i < s1_len)
	{
		strj[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		strj[i++] = s2[j++];
	strj[i] = '\0';
	free(s1);
	return (strj);
}

char	*ft_strdup_gnl(const char *s1)
{
	int		i;
	char	*s2;
	size_t	s1_len;

	i = 0;
	s1_len = ft_strlen_gnl(s1);
	s2 = malloc(sizeof(char) * (s1_len + 1));
	if (!s2)
		return (NULL);
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
