/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:30 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/21 15:19:16 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*d;
	unsigned const char	*s;

	i = 0;
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	if (src > dst)
	{
		while (i < len && (src != 0 || dst != 0))
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		while (len > 0 && (src != 0 || dst != 0))
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}
	return (dst);
}
/*
int main()
{
	char str1[] = "aaaaaa";
	char str2[] = "bbb"; 
	char dst[] = "aaaaaa";
    char src[] = "bbb"; 

    puts("str1 before memmove original ");
    puts(str1);

   // Copies contents of str2 to sr1 
    memmove(str1, str2, 5);
    puts("str1 after memmove original");
    puts(str1);
	
    puts("\nstr3 before memmove ");
    puts(dst);

    // Copies contents of str2 to sr1
    ft_memmove(dst, src, 5);
    puts("str3 after memmove");
	puts(dst);

    return 0;
}
*/
