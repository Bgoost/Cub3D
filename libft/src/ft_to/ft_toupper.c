/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_toupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:53:40 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/13 12:11:46 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	else
		return (c);
}

/*
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("%i", ft_toupper(argv[1][0]));
        printf("%i", toupper(argv[1][0]));
    }
    return 0;
}
*/
