/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/02/13 19:26:29 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/02/13 19:26:29 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	free_textures(t_textures *textures)
{
	
	if (textures->north)
	{

		free(textures->north);
		textures->north = NULL;
	}
	if (textures->south)
	{
		free(textures->south);
		textures->south = NULL;
	}
	if (textures->west)
	{
		free(textures->west);
		textures->west = NULL;
	}
	if (textures->east)
	{
		free(textures->east);
		textures->east = NULL;
	}
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
}

void	free_scene(t_map **scene)
{
	if (!scene || !(*scene))
		return ;
	free_textures(&(*scene)->textures);
	if ((*scene)->lines)
	{
		free_map((*scene)->lines);
		(*scene)->lines = NULL;
	}
	if ((*scene)->map)
	{
		free_map((*scene)->map);
		(*scene)->map = NULL;
	}
	free(*scene);
	*scene = NULL;
}

void	free_anim(t_game *game)
{
	int	i;

	i = 0;
	if (game->anim)
	{
		while (i < 6)
		{
			if (game->anim->sprite_paths[i])
				free(game->anim->sprite_paths[i]);
			i++;
		}
		while (i < 12)
		{
			if (game->anim->player_sprites[i - 6])
				mlx_delete_image(game->mlx, game->anim->player_sprites[i - 6]);
			i++;
		}
		while (i < 18)
		{
			if (game->anim->player_texture[i - 12])
				mlx_delete_texture(game->anim->player_texture[i - 12]);
			i++;
		}
		free(game->anim);
	}
}

void	free_game(t_game *game)
{
	free_anim(game);
	mlx_delete_image(game->mlx, game->image);
	mlx_terminate(game->mlx);
	free_mlx_textures(game->textures);
	free(game->ray);
	free(game);
}
