/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/03/05 18:42:13 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

double	point_distance(t_point hit, t_point player)
{
	double	distance;
	t_point	grid_player;

	grid_player.x = (player.x * TILE);
	grid_player.y = (player.y * TILE);
	distance = sqrt(pow((grid_player.x - hit.x), 2)
			+ pow((grid_player.y - hit.y), 2));
	return (distance);
}

void	set_distance(double distance, t_ray *ray, t_point *hit_point, char id)
{
	ray->distance_to_wall = distance;
	ray->hit_point = hit_point;
	ray->wall_hit = id;
}

void	get_distance(t_point *v_hit, t_point *h_hit, t_ray *ray, t_game *info)
{
	double	v_distance;
	double	h_distance;

	v_distance = point_distance(*v_hit, info->player);
	h_distance = point_distance(*h_hit, info->player);
	if (v_distance < h_distance)
	{
		set_distance(v_distance, ray, v_hit, 'v');
		printf("freeing h_hit %p\n", h_hit);
		free(h_hit);
	}
	else
	{
		set_distance(h_distance, ray, h_hit, 'h');
		printf("freeing v_hit %p\n", v_hit);
		free(v_hit);
	}
	ray->distance_to_wall = ray->distance_to_wall
		* cos(degree_to_radian(ray->angle - info->direction));
}

int	cast_ray(t_game *info, char **map, t_ray *ray)
{
	t_point	*v_hit;
	t_point	*h_hit;
	t_point	center;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;
	h_hit = horizontal_hit(info->player, map, ray->angle, info);
	if (!h_hit)
		return (0);
	v_hit = vertical_hit(info->player, map, ray->angle, info);
	if (!v_hit)
	{
		printf("freeing h_hit %p\n", h_hit);
		return (free(h_hit), 0);
	}
	get_distance(v_hit, h_hit, ray, info);
	ray->projection_height = (TILE / ray->distance_to_wall)
		* info->distance_to_plane;
	ray->projection_height = ceil(ray->projection_height);
	ray->first_wall_pixel = center.y - (ray->projection_height / 2);
	ray->last_wall_pixel = ray->first_wall_pixel + ray->projection_height;
	if (ray->projection_height > WIN_HEIGHT - 1 || ray->projection_height < 0)
		adjust_pixels(&ray->first_wall_pixel, &ray->last_wall_pixel);
	return (1);
}
