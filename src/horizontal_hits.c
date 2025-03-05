/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_hits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:38:47 by martalop          #+#    #+#             */
/*   Updated: 2025/03/05 18:39:26 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_point	*first_h_hit(double angle, t_point player)
{
	t_point	grid_player;
	t_point	*hit;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE;
	grid_player.y = player.y * TILE;
	if (angle <= 180 && angle >= 0)
		hit->y = floor(grid_player.y / TILE) * TILE - 0.0000000001;
	else
		hit->y = floor(grid_player.y / TILE) * TILE + TILE;
	hit->x = grid_player.x
		+ (grid_player.y - hit->y) / tan(degree_to_radian(angle));
	return (hit);
}

void	horizontal_increments(double angle, t_point *increment)
{
	if (angle >= 0 && angle <= 180)
		increment->y = -TILE;
	else
		increment->y = TILE;
	if (angle >= 90 && angle <= 270)
		increment->x = -fabs(TILE / tan(degree_to_radian(angle)));
	else
		increment->x = fabs(TILE / tan(degree_to_radian(angle)));
}

t_point	*horizontal_hit(t_point player, char **map, double angle, t_game *info)
{
	t_point	*hit;
	t_point	increment;

	hit = first_h_hit(angle, player);
	if (!hit)
		return (NULL);
	if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
		return (hit);
	horizontal_increments(angle, &increment);
	while (map[(int)hit->y / TILE][(int)hit->x / TILE] == '0')
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
		if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height))
			return (hit);
	}
	return (hit);
}
