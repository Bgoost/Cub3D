/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:26:16 by martalop          #+#    #+#             */
/*   Updated: 2025/02/19 16:25:50 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	validate_textures(t_textures textures)
{
	if (access(textures.north, R_OK))
	{
		perror("Error:\nNorth texture");
		return (0);
	}
	if (access(textures.west, R_OK))
	{
		perror("Error:\nWest texture");
		return (0);
	}
	if (access(textures.south, R_OK))
	{
		perror("Error:\nSouth texture");
		return (0);
	}
	if (access(textures.east, R_OK))
	{
		perror("Error:\nEast texture");
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
	info->player.x = player_x;
	info->player.y = player_y;
}

int	init_mlx(t_game *info)
{
	info->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", false);
	if (!info->mlx)
		return (1);
	info->image = mlx_new_image(info->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!info->image)
	{
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
	if (validate_textures(textures))
		info->textures = textures;
	else
	{
		free_game(info);
		return (1);
	}
	return (0);
}

t_game	*init_raycasting(t_map map)
{
	t_game	*info;

	info = malloc(sizeof(t_game) * 1);
	if (!info)
		return (NULL);
	info->ray_increment = (double)FOV / (double)WIN_WIDTH;
	info->distance_to_plane = (WIN_WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	init_player(map.player_c, map.player_x, map.player_y, info);
	info->map = map.map;
	info->map_height = map.height;
	info->map_width = map.width;
	if (init_mlx(info) == 1)
		return (free(info), NULL);
	info->ray = malloc(sizeof(t_ray) * 1);
	if (!info->ray)
	{
		free_game(info);
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	}
	info->ray->wall_hit = '\0';
	if (init_textures(info, map.textures) == 1)
		return (NULL);
	return (info);
}
