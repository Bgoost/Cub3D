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
#include "../inc/cub3d.h"

t_anim	*init_anim(void)
{
	t_anim	*anim;
	int		i;

	i = 0;
	anim = (t_anim *)malloc(sizeof(t_anim));
	if (!anim)
		return (NULL);
	anim->is_animating = 0;
	anim->last_frame_time = 0.0;
	anim->current_frame = 0;
	while (i < 6)
		anim->player_sprites[i++] = NULL;
	while (i < 12)
		anim->sprite_paths[i++ - 6] = NULL;
	while (i < 18)
		anim->player_texture[i++ - 12] = NULL;
	return (anim);
}

static void	init_and_set(t_game *game)
{
	int	i;

	game->anim->sprite_paths[0] = ft_strdup("sprites/anim/anim_1.png");
	game->anim->sprite_paths[1] = ft_strdup("sprites/anim/anim_2.png");
	game->anim->sprite_paths[2] = ft_strdup("sprites/anim/anim_3.png");
	game->anim->sprite_paths[3] = ft_strdup("sprites/anim/anim_4.png");
	game->anim->sprite_paths[4] = ft_strdup("sprites/anim/anim_5.png");
	game->anim->sprite_paths[5] = ft_strdup("sprites/gun.png");
	i = 0;
	while (i < 6)
	{
		if (!game->anim->sprite_paths[i])
		{
			exit_error("\033[31mError:\nFailed to allocate memory\
for sprite path\033[0m\n");
			while (i >= 0)
				free(game->anim->sprite_paths[i--]);
			exit_error("");
		}
		i++;
	}
}

void	load_player_sprite(t_game *game)
{
	int				i;
	int				j;
	mlx_texture_t	*texture;

	init_and_set(game);
	i = 0;
	j = 0;
	while (i < 5)
	{
		texture = mlx_load_png(game->anim->sprite_paths[i]);
		if (!texture)
		{
			printf("\033[31mError:\nFailed to load\
 sprite: %s\033[0m\n", game->anim->sprite_paths[i]);
			while (j < i)
			{
				mlx_delete_texture(game->anim->player_texture[j]);
				j++;
			}
			exit_error("");
		}
		game->anim->player_texture[i] = texture;
		i++;
	}
}
