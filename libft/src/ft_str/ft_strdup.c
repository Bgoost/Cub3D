/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:26:48 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/16 18:08:51 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*tmp;
	int		i;

	i = 0;
	tmp = (char *)s1;
	s2 = (char *)malloc(ft_strlen(s1)+ 1);
	if (!s2)
		return (0);
	while (s1[i] != '\0')
	{
		s2[i] = tmp[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
/*
int main()
{
    char source[] = "GeeksForGeeks";

    // A copy of source is created dynamically
    // and pointer to copy is returned.
    char *target = strdup(source);
    char *target2 = ft_strdup(source);

    printf("%s\n", target2);
    printf("%s", target);
    return 0;
}
*/
