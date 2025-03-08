/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: martalop <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/22 20:07:39 by martalop		   #+#	  #+#			  */
/*	 Updated: 2025/03/03 22:14:08 by martalop		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_error(char *msg)
{
	printf("\033[31m%s\033[0m", msg);
	exit(1);
}

void	print_scene(t_game *info, char **map, t_ray *ray)
{
	int		x;

	x = 0;
	ray->angle = info->direction + (FOV / 2);
	while (x < WIN_WIDTH)
	{
		ray->angle = adjust_angle(ray->angle);
		if (!cast_ray(info, map, ray))
			exit (1);
		print_column(ray, info, x);
		free(ray->hit_point);
		ray->angle = ray->angle - info->ray_increment;
		x++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	game = NULL;
	map = NULL;
	if (!main_checker(argc, argv, &map))
		return (1);
	game = init_raycasting(map);
	if (!game)
	{
		free_scene(&map);
		return (1);
	}
	free_scene(&map);
	print_scene(game, game->map, game->ray);
	mlx_loop_hook(game->mlx, (void *)player_movements, game);
	mlx_loop(game->mlx);
	free_scene(&map);
	free_game(game);
	return (0);
}
