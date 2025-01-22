/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:09:38 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/21 15:30:04 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*last;

	last = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
		{
			last = (char *)&s[i];
			i++;
		}
		else
			i++;
	}
	if ((char)c == s[i])
		last = (char *)&s[i];
	return (last);
}
/*
int main()
{
	printf("%s", ft_strrchr("hola que tal", 108));
}
*/
