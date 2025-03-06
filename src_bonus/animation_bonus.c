/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 animation.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/03/05 17:09:43 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/03/05 17:09:43 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../inc/cub3d_bonus.h"

static void	delete_current_sprite(t_game *game)
{
	int	current_frame;

	current_frame = game->anim->current_frame;
	if (game->anim->player_sprites[current_frame])
	{
		printf("freeing player_sprites[%d] %p\n", current_frame,
			game->anim->player_sprites[current_frame]);
		mlx_delete_image(game->mlx, game->anim->player_sprites[current_frame]);
		game->anim->player_sprites[current_frame] = NULL;
	}
}

static int	load_next_sprite(t_game *game, int next_frame)
{
	int	j;

	if (!game->anim->player_texture[next_frame])
	{
		j = 0;
		while (j < next_frame)
		{
			printf("freeing player_texture[%d] %p\n", j,
				game->anim->player_texture[j]);
			mlx_delete_texture(game->anim->player_texture[j]);
			j++;
		}
		printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n",
			game->anim->sprite_paths[next_frame]);
		exit_error("");
		return (0);
	}
	return (1);
}

static void	display_next_sprite(t_game *game, int next_frame)
{

	game->anim->player_sprites[next_frame] = mlx_texture_to_image(game->mlx,
			game->anim->player_texture[next_frame]);
	printf("freeing player_sprites[%d] %p\n", next_frame,
		game->anim->player_sprites[next_frame]);
	if (!game->anim->player_sprites[next_frame])
	{
		printf("\033[31mError:\nFailed to convert texture to\
image for sprite %d\033[0m\n", next_frame);
		exit_error("");
	}

	mlx_image_to_window(game->mlx, game->anim->player_sprites[next_frame],
		10, 0);
	game->anim->current_frame = next_frame;
}

void	update_animation(void *param)
{
	t_game	*game;
	double	current_time;
	int		next_frame;

	game = (t_game *)param;
	if (!game->anim->is_animating)
		return ;
	current_time = mlx_get_time();
	if (current_time - game->anim->last_frame_time < 0.05)
		return ;
	game->anim->last_frame_time = current_time;
	next_frame = game->anim->current_frame + 1;
	delete_current_sprite(game);
	if (next_frame < 5)
	{
		if (load_next_sprite(game, next_frame))
			display_next_sprite(game, next_frame);
	}
	else
		game->anim->is_animating = false;
}

void	test_cursor(void *param)
{
	t_game	*info;

	info = (t_game *)param;
	if (mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !info->anim->is_animating)
	{
		info->anim->is_animating = true;
		info->anim->current_frame = 0;
		info->anim->last_frame_time = mlx_get_time();
	}
}
