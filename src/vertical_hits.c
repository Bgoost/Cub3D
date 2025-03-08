/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_hits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:37:49 by martalop          #+#    #+#             */
/*   Updated: 2025/03/08 21:17:46 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_point	*first_v_hit(double angle, t_point player)
{
	t_point	*hit;
	t_point	grid_player;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE;
	grid_player.y = player.y * TILE;
	if (angle <= 270 && angle >= 90)
		hit->x = floor(grid_player.x / TILE) * TILE - 0.0000000001;
	else
		hit->x = floor(grid_player.x / TILE) * TILE + TILE;
	hit->y = grid_player.y
		+ (grid_player.x - hit->x) * tan(degree_to_radian(angle));
	return (hit);
}

void	vertical_increment(double angle, t_point *increment)
{
	if (angle <= 270 && angle >= 90)
		increment->x = -TILE;
	else
		increment->x = TILE;
	if (angle <= 180 && angle >= 0)
		increment->y = -fabs(TILE * tan(degree_to_radian(angle)));
	else
		increment->y = fabs(TILE * tan(degree_to_radian(angle)));
}

t_point	*vertical_hit(t_point player, char **map, double angle, t_game *info)
{
	t_point	*hit;
	t_point	increment;

	hit = first_v_hit(angle, player);
	if (!hit)
		return (NULL);
	if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
		return (hit);
	vertical_increment(angle, &increment);
	while (map[((int)hit->y / TILE)][(int)hit->x / TILE] == '0')
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
		if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height))
			return (hit);
	}
	return (hit);
}
