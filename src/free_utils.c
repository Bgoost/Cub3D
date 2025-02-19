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
void	free_sprites(t_sprite **lst)
{
	t_sprite	*tmp;
	t_sprite	*next;

	if (*lst && lst)
	{
		tmp = *lst;
		while (tmp)
		{
			next = tmp->next;
			free(tmp);
			tmp = next;
		}
		*lst = NULL;
	}
}