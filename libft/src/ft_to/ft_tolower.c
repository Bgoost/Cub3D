/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tolower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:39:25 by crmanzan          #+#    #+#             */
/*   Updated: 2023/09/13 12:40:56 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <ctype.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c += 32);
	else
		return (c);
}

/*
int main(int argc, char *argv[])
{
    if(argc == 2)
    {
        printf("%i", ft_tolower(argv[1][0]));
        printf("%i", tolower(argv[1][0]));
    }
    return 0;
}
*/
