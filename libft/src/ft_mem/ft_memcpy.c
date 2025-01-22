/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:45:53 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/22 13:50:29 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned const char	*s;
	unsigned char		*d;
	size_t				i;

	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (dst == src || !n)
		return (dst);
	printf("n: %zu, i: %zu\n", n, i);
	while (n > i)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
/*
int main()
{
	char str1[] = "Hsfdfdsola"; // Array of size 100
	char str2[] = "Adios"; // Array of size 100
	char dst[] = "aa"; // Array of size 100
    char src[] = "bbb"; // Array of size 5

    puts("str1 before memmove original ");
    puts(str1);

   // Copies contents of str2 to sr1
    memmove(str1, str2, 2);
    puts("str1 after memmove original");
    puts(str1);

    puts("\nstr3 before memmove ");
    puts(dst);

    // Copies contents of str2 to sr1
    ft_memcpy(dst, src, 2);
    puts("str3 after memmove");
	puts(dst);

    return 0;
}
*/
