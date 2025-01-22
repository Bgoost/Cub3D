/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isascii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:59:39 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/13 12:17:06 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 0177)
		return (1);
	else
		return (0);
}

/*
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("%i", ft_isascii(argv[1][0]));
        printf("%i", isascii(argv[1][0]));
    }
    return 0;
}
*/
