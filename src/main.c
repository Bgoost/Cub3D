/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:07:39 by martalop          #+#    #+#             */
/*   Updated: 2025/02/23 20:07:47 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_error(char *msg)
{
	printf("\033[31m%s\n\033[0m", msg);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	if (!main_checker(argc, argv, &map))
		return (1);
	game = init_raycasting(*map);
	if (!game)
	{
		free_scene(&map);
		return (1);
	}
	load_player_sprite(game);
    // init_anim(game);
    
	print_scene(game, game->map, game->ray);
//	mlx_key_hook(game->mlx, key_input, game);
	mlx_loop_hook(game->mlx, (void *)player_movements, game);
	mlx_loop_hook(game->mlx, (void *)test_cursor, game);
    // mlx_loop_hook(game->mlx, update, game);
	
	mlx_loop(game->mlx);
	free_game(game);
	free_scene(&map);
	return (0);
}
