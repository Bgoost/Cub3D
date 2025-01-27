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
	info->ray_increment = FOV / WIDTH;
	info->distance_to_plane = (WIDTH / 2)/(tan(FOV/2));
	if (map.player_c == N)
		info->angle = 90;
	else if (map.player_c == S)
		info->angle = 270;
	else if (map.player_c == W)
		info->angle = 180;
	else if (map.player_c == E)
		info->angle = 360;
	info->player.x = map.plaxer_x;
	info->player.y = map.plaxer_y;

	printf("ray increment: %d\n", info->ray_increment);
	printf("distance_to_plane: %d\n", info->distance_to_plane);
	printf("angle: %d\n", info->angle);
}
