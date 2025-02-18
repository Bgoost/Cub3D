/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:26:16 by martalop          #+#    #+#             */
/*   Updated: 2025/02/18 20:27:55 by martalop         ###   ########.fr       */
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

t_raycasting	*init_raycasting(t_map map)
{
	t_raycasting	*info;

	info = malloc(sizeof(t_raycasting) * 1);
	if (!info)
		return (NULL);
	info->ray_increment = (double)FOV / (double)WIN_WIDTH;
	info->distance_to_plane = (WIN_WIDTH / 2) / tan(degree_to_radian(FOV / 2));
	if (map.player_c == 'N')
		info->direction = 90;
	else if (map.player_c == 'S')
		info->direction = 270;
	else if (map.player_c == 'W')
		info->direction = 180;
	else if (map.player_c == 'E')
		info->direction = 0;
	info->player.x = map.player_x;
	info->player.y = map.player_y;
	info->map_height = map.height;
	info->map_width = map.width;
	info->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "MLX42", false);
	if (!info->mlx)
		return (NULL);
	info->image = mlx_new_image(info->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!info->image)
	{
		free(info->mlx);
		return (NULL);
	}
	mlx_image_to_window(info->mlx, info->image, 0, 0);
	info->ray = malloc(sizeof(t_ray) * 1);
	if (!info->ray)
	{
		free_array(info->map);
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	}
	info->ray->wall_hit = '\0';
	info->map = map.map;
	if (validate_textures(map.textures))
		info->textures = map.textures;
	else
	{
		mlx_delete_image(info->mlx, info->image);
		mlx_terminate(info->mlx);
		free(info->ray);
		free(info);
		return (NULL);
	}
	return (info);
}
