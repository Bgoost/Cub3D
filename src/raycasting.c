/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:26:16 by martalop          #+#    #+#             */
/*   Updated: 2025/01/27 20:33:58 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_raycasting	*init_raycasting(t_map map)
{
	t_raycasting *info;

	info = malloc(sizeof(t_raycasting) * 1);
	if (!info)
		return (NULL);
	info->ray_increment = (double)FOV / (double)WIDTH;
	info->distance_to_plane = (WIDTH / 2)/(tan(degree_to_radian(FOV/2)));
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
	info->height = map.height;
	info->width = map.width;
	info->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!info->mlx)
		return (NULL);
	info->image = mlx_new_image(info->mlx, WIDTH, HEIGHT);
	if (!info->image)
	{
		free(info->mlx);
		return (NULL);
	}
	info->ray = malloc(sizeof(t_ray) * 1);
	if (!info->ray)
	{
		free_array(info->map);
		return (ft_putstr_fd("malloc error\n", 2), NULL);
	}
	info->map = map.map;
	printf("ray increment: %f\n", info->ray_increment);
	printf("distance_to_plane: %f\n", info->distance_to_plane);
	printf("angle: %f\n", info->direction);
	return (info);
}
