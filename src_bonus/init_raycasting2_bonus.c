/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting2_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:46:14 by martalop          #+#    #+#             */
/*   Updated: 2025/03/06 14:00:00 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	print_map(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		printf("map[%d] = %s\n", y, map[y]);
		y++;
	}
	printf("\n");
}

int	validate_textures(t_textures textures)
{
	if (access(textures.north, R_OK))
	{
		perror("\033[31mError:\nNorth texture");
		return (0);
	}
	if (access(textures.west, R_OK))
	{
		perror("\033[31mError:\nWest texture");
		return (0);
	}
	if (access(textures.south, R_OK))
	{
		perror("\033[31mError:\nSouth texture");
		return (0);
	}
	if (access(textures.east, R_OK))
	{
		perror("\033[31mError:\nEast texture");
		return (0);
	}
	return (1);
}

void	init_player(char player_c, int player_x, int player_y, t_game *info)
{
	if (player_c == 'N')
		info->direction = 90;
	if (player_c == 'S')
		info->direction = 270;
	if (player_c == 'W')
		info->direction = 180;
	if (player_c == 'E')
		info->direction = 0;
	info->player.x = player_x + 0.5;
	info->player.y = player_y + 0.5;
}

int	init_mlx(t_game *info)
{
	info->mlx = NULL;
	info->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "CUB3D", false);
	printf("malloc mlx: %p\n", info->mlx);
	if (!info->mlx)
		return (1);
	info->image = mlx_new_image(info->mlx, WIN_WIDTH, WIN_HEIGHT);
	printf("malloc image: %p\n", info->image);
	if (!info->image)
	{
		printf("freeing info->mlx %p\n", info->mlx);
		free(info->mlx);
		return (1);
	}
	if (mlx_image_to_window(info->mlx, info->image, 0, 0) < 0)
	{
		ft_putstr_fd("could not put image to window\nexiting..", 2);
		mlx_close_window(info->mlx);
		exit(1);
	}
	return (0);
}

int	init_textures(t_game *info, t_textures textures)
{
	info->textures = malloc(sizeof(t_mlx_textures) * 1);
	printf("malloc textures: %p\n", info->textures);
	if (!info->textures)
	{
		free_game(info);
		return (1);
	}
	info->textures->north = NULL;
	info->textures->south = NULL;
	info->textures->east = NULL;
	info->textures->west = NULL;
	if (validate_textures(textures))
	{
		info->textures->north = mlx_load_png(textures.north);
		printf("malloc north: %p\n", info->textures->north);
		info->textures->south = mlx_load_png(textures.south);
		printf("malloc south: %p\n", info->textures->south);
		info->textures->west = mlx_load_png(textures.west);
		printf("malloc west: %p\n", info->textures->west);
		info->textures->east = mlx_load_png(textures.east);
		printf("malloc east: %p\n", info->textures->east);
		if (!info->textures->north || !info->textures->south
			|| !info->textures->west || !info->textures->east)
		{
			free_game(info);
			return (1);
		}
		info->floor_color = get_floor_color(textures.floor_color);
		info->ceiling_color = get_ceiling_color(textures.ceiling_color);
	}
	else
	{
		free_game(info);
		return (1);
	}
	return (0);
}
