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
		printf("freeing textures->north %p\n", textures->north);
		printf("free: %p\n", textures->north);
		free(textures->north);
		textures->north = NULL;
	}
	if (textures->south)
	{
		printf("freeing textures->south %p\n", textures->south);
		free(textures->south);
		textures->south = NULL;
	}
	if (textures->west)
	{
		printf("freeing textures->west %p\n", textures->west);
		free(textures->west);
		textures->west = NULL;
	}
	if (textures->east)
	{
		printf("freeing textures->east %p\n", textures->east);
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
		printf("freeing map[%d] %p\n", i, map[i]);
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
		printf("hola lines\n");
		(*scene)->lines = NULL;
	}
	if ((*scene)->map)
	{
		free_map((*scene)->map);
		printf("hola map\n");
		(*scene)->map = NULL;
	}
	printf("freeing scene %p\n", *scene);
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
			{
				printf("freeing game->anim->sprite_paths[%d] %p\n", i, game->anim->sprite_paths[i]);
				free(game->anim->sprite_paths[i]);
			}
			i++;
		}
		while (i < 12)
		{
			if (game->anim->player_sprites[i - 6])
			{
				printf("freeing game->anim->player_sprites[%d] %p\n", (i - 6), game->anim->player_sprites[i - 6]);
				mlx_delete_image(game->mlx, game->anim->player_sprites[i - 6]);
			}
			i++;
		}
		while (i < 18)
		{
			if (game->anim->player_texture[i - 12])
			{
				printf("freeing game->anim->player_texture[%d] %p\n", (i - 12), game->anim->player_texture[i - 12]);
				mlx_delete_texture(game->anim->player_texture[i - 12]);
			}
			i++;
		}
		printf("freeing game->anim %p\n", game->anim);
		free(game->anim);
	}
}

void	free_game(t_game *game)
{
	free_anim(game);
	if (game->textures)
		free_mlx_textures(game->textures);
	//printf("delete game->image %p\n", game->image);
	if(game->mlx != NULL)
	{
		printf("terminate game->mlx %p\n", game->mlx);
		printf("PRINT\n");
		if (game->image)
			mlx_delete_image(game->mlx, game->image);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		printf("freeing gam->ray %p\n", game->ray);

	}
	free(game->ray);
	printf("freeing game %p\n", game);
	free(game);
}
