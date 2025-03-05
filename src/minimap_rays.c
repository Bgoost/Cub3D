/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:49:00 by martalop          #+#    #+#             */
/*   Updated: 2025/03/05 16:50:41 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_safe_mini_ray(t_point ray_pos, t_game *game)
{
	if (!safe_map_point(ray_pos.x, ray_pos.y,
			game->map_width, game->map_height))
		return (0);
	if (is_wall(ray_pos.x, ray_pos.y, game))
		return (0);
	return (1);
}

void	print_mini_ray(t_game *game, t_point ray_dir, t_point ray_pos)
{
	int		mini_x;
	int		mini_y;
	int		hit;
	double	step_size;

	step_size = 0.05;
	hit = 0;
	while (!hit)
	{
		ray_pos.x += ray_dir.x * step_size;
		if (!is_safe_mini_ray(ray_pos, game))
			hit = 1;
		ray_pos.y += ray_dir.y * step_size;
		if (!is_safe_mini_ray(ray_pos, game))
			hit = 1;
		mini_x = (ray_pos.x - (game->player.x - MINIMAP_SCALE / 2))
			* (MINIMAP_SIZE / MINIMAP_SCALE);
		mini_y = (ray_pos.y - (game->player.y - MINIMAP_SCALE / 2))
			* (MINIMAP_SIZE / MINIMAP_SCALE);
		if (mini_x < 0 || mini_x >= MINIMAP_SIZE
			|| mini_y < 0 || mini_y >= MINIMAP_SIZE)
			break ;
		mlx_put_pixel(game->image, mini_x + MINIMAP_X_OFFSET,
			mini_y + MINIMAP_Y_OFFSET, RAY_COLOR);
	}
}

void	draw_minimap_rays(t_game *game)
{
	t_point	ray_pos;
	t_point	ray_dir;
	double	angle;
	double	increment;
	int		i;

	i = 0;
	ray_pos.x = game->player.x;
	ray_pos.y = game->player.y;
	angle = game->direction + (FOV / 2);
	increment = (double)FOV / (double)WIN_WIDTH;
	while (i < WIN_WIDTH)
	{
		angle = adjust_angle(angle);
		ray_dir.x = cos(degree_to_radian(angle));
		ray_dir.y = -sin(degree_to_radian(angle));
		print_mini_ray(game, ray_dir, ray_pos);
		angle = angle - increment;
		i++;
	}
}
