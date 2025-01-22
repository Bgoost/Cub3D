/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:58:44 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/22 13:41:23 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	is_in(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s2;
	size_t	i;
	size_t	end;
	size_t	len;

	if (!s1 || !set)
		return (0);
	i = 0;
	len = ft_strlen(s1);
	end = len - 1;
	while (is_in(set, s1[i]))
		i++;
	if (i == len)
		return (ft_strdup(""));
	while (is_in(set, s1[end]))
		end--;
	s2 = (char *)malloc((end - i + 2) * sizeof(char));
	if (!s2)
		return (0);
	ft_strlcpy(s2, (char *)(s1 + i), end - i + 2);
	return (s2);
}
/*
int main()
{
	const char s1[] = "ababc";
	const char set[] = "abc";
	printf("%s\n", ft_strtrim(s1, set));
	return 0;
}
*/
