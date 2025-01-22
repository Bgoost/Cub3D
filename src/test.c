/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:37:42 by martalop          #+#    #+#             */
/*   Updated: 2025/01/19 22:34:47 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

char	**create_map(void)
{
	char	**map;
	int		x;
	
	x = 0;
	map = malloc(sizeof(char *) * 5);
	while (x < 4)
	{
		map[x] = malloc(sizeof(char) * 4);
		x++;
	}
	map[x] = NULL;
	x = 0;
	if ( x == 0)
	{
		for (i = 0; i < 4, i++)
		{
			map[x][i] = '1';
		}
	}	
}

int	main(void)
{
	char	**map;

	map = create_map();

}
