/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:26:16 by martalop          #+#    #+#             */
/*   Updated: 2025/03/07 23:02:35 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	free_mlx_textures(t_mlx_textures *textures)
{
	if (textures->north)
		mlx_delete_texture(textures->north);
	if (textures->south)
		mlx_delete_texture(textures->south);
	if (textures->west)
		mlx_delete_texture(textures->west);
	if (textures->east)
		mlx_delete_texture(textures->east);
	free(textures);
}

int	is_same_char(char a, char b)
{
	if (a == b)
		return (1);
	return (0);
}

void	replace_player_pos(char **map, char id)
{
	int	x;	
	int	y;	

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_same_char(map[y][x], id))
				map[y][x] = '0';
			x++;
		}
		y++;
	}
}

int	init_ray(t_game *info)
{
	info->ray = malloc(sizeof(t_ray) * 1);
	if (!info->ray)
	{
		free_game(info);
		return (ft_putstr_fd("malloc error\n", 2), 1);
	}
	info->ray->wall_hit = '\0';
	return (0);
}

char	**copy_map(char **map, int height)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	while (i < height)
	{
		new_map[i] = ft_strdup(map[i]);
		if (!new_map[i])
		{
			free_map(new_map);
			return (NULL);
		}
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

t_game	*init_raycasting(t_map *map)
{
	t_game	*info;

	info = NULL;
	info = malloc(sizeof(t_game) * 1);
	if (!info)
		return (NULL);
	ft_bzero(info, sizeof(t_game));
	info->ray_increment = (double)FOV / (double)WIN_WIDTH;
	info->distance_to_plane = (WIN_WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	init_player(map->player_c, map->player_x, map->player_y, info);
	info->map = copy_map(map->map, map->height);
	replace_player_pos(info->map, map->player_c);
	info->map_height = map->height;
	info->map_width = map->width;
	info->anim = init_anim();
	if (!info->anim)
	{
		printf("\033[31mError:\nFailed to initialize animation\033[0m\n");
		free_game(info);
		exit_error("");
	}
	if (init_ray(info) || init_textures(info, &map->textures) == 1)
		return (NULL);
	if (init_mlx(info) == 1)
		return (free_game(info), NULL);
	return (info);
}
