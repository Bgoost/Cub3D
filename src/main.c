/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:07:39 by martalop          #+#    #+#             */
/*   Updated: 2025/02/17 21:50:03 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void exit_error(char* msg)
{
    printf("\033[31m%s\n\033[0m", msg);
    exit(1);
}

int main(int argc, char **argv)
{
    t_map *map;
    t_raycasting  *game;
    if(!main_checker(argc, argv, &map))
        return 1;
    printf("All good, freeing map\n");
    game = init_raycasting(*map);
    print_scene(game, game->map, game->ray);
	mlx_key_hook(game->mlx, keyboard_input, game);
	mlx_loop(game->mlx);
	free_game(game);
	free_scene(&map);
    return 0;
}

/*void print_error(char *msg)
{
    printf("\033[41mError\033[0m\n");
    printf("\033[31m%s\n\033[0m", msg);
}*/
