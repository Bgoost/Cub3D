/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:05:04 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/21 15:24:22 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned const char	*ptr;

	ptr = (unsigned const char *)s;
	i = 0;
	while (i < n)
	{
		if (*ptr == (unsigned const char)c)
		{
			return ((void *)s);
		}
		else
		{
			i++;
			ptr++;
			s++;
		}
	}
	return (0);
}

/*
int main () {
   const char str[] = "/|\x12\xff\x09\x42\2002\42|\\";
   const char ch = 'f';
   char *ret;

	printf("La string sin modificar es: %s\n", str);
   //ret = memchr(str, ch, strlen(str));
   ret = ft_memchr(str, '\200', 10);
   printf("String after |%c| is - |%s|\n", ch, ret);

   return(0);
}
*/
