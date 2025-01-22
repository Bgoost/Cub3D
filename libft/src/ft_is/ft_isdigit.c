/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:39:28 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/13 12:57:41 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

/*
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("%i", ft_isdigit(argv[1][0]));
        printf("%i", isdigit(argv[1][0]));
    }
    return 0;
}
*/
