/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_isprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:17:26 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/21 14:52:19 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	else
		return (0);
}

/*
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("%i", ft_isprint(argv[1][0]));
        printf("%i", isprint(argv[1][0]));
    }
    return 0;
}
*/
