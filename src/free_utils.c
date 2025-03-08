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

#include "../inc/cub3d.h"

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

void	free_game(t_game *game)
{
	free_map(game->map);
	if (game->textures)
		free_mlx_textures(game->textures);
	if (game->mlx != NULL)
	{
		if (game->image)
			mlx_delete_image(game->mlx, game->image);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	free(game->ray);
	free(game);
}
