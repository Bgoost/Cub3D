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

#include "../inc/cub3d_bonus.h"

void	exit_error(char *msg)
{
	printf("\033[31m%s\n\033[0m", msg);
	exit(1);
}

void	main_anim_init(t_game *game, t_anim *anim)
{
	load_player_sprite(game);
	anim->player_texture[5] = mlx_load_png(anim->sprite_paths[5]);
	if (!anim->player_texture[5])
	{
		exit_error("\033[31mError:\nFailed to load sprite\033[0m");
		exit_error("");
	}
	anim->player_sprites[5] = \
			mlx_texture_to_image(game->mlx, anim->player_texture[5]);
	if (!anim->player_sprites[5])
	{
		printf("\033[31mError:\nFailed to convert texture \
to image for sprite %d\033[0m", 5);
		exit_error("");
	}
	mlx_image_to_window(game->mlx, game->anim->player_sprites[5], 0, 0);
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
	draw_minimap(info->image, info->map, info);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_game	*game;

	game = NULL;
	map = NULL;
	if (!main_checker(argc, argv, &map))
		return (1);
	printf("map: %p\n", map);
	game = init_raycasting(*map);
	if (!game)
	{
		free_scene(&map);
		return (1);
	}
	main_anim_init(game, game->anim);
	print_scene(game, game->map, game->ray);
	mlx_loop_hook(game->mlx, (void *)player_movements, game);
	mlx_loop(game->mlx);
	free_scene(&map);
	free_game(game);
	return (0);
}
