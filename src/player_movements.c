/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:22:41 by martalop          #+#    #+#             */
/*   Updated: 2025/03/05 18:41:28 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	handle_ws_movements(t_game *info, mlx_t *mlx, t_point tmp)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		tmp.y -= 0.1001 * sin(degree_to_radian(info->direction));
		tmp.x += 0.1001 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, info->player.y, info->map_width,
				info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width,
				info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		tmp.y += 0.1001 * sin(degree_to_radian(info->direction));
		tmp.x -= 0.1001 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, info->player.y, info->map_width,
				info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width,
				info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
}

void	handle_ad_movements(t_game *info, mlx_t *mlx, t_point tmp)
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		tmp.x -= 0.1001 * sin(degree_to_radian(info->direction));
		tmp.y -= 0.1001 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, info->player.y, info->map_width,
				info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width,
				info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		tmp.x += 0.1001 * sin(degree_to_radian(info->direction));
		tmp.y += 0.1001 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, info->player.y, info->map_width,
				info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width,
				info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
}

void	handle_arrow_fov(t_game *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->direction += 2.5;
		print_scene(info, info->map, info->ray);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 2.5;
		print_scene(info, info->map, info->ray);
	}
}

/*void	handle_fire_anim(t_game *info)
{
	if ((mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT)
			|| mlx_is_key_down(info->mlx, MLX_KEY_SPACE))
		&& !info->anim->is_animating)
	{
		printf("Pium Pium\n");
		info->anim->is_animating = true;
		info->anim->current_frame = 0;
		info->anim->last_frame_time = mlx_get_time();
	}
}*/

void	player_movements(void *param)
{
	t_game	*info;
	t_point	tmp;

	info = (t_game *)param;
	tmp.x = info->player.x;
	tmp.y = info->player.y;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(info->mlx, info->image);
		mlx_close_window(info->mlx);
		exit(0);
	}
	// BONUS
	// handle_fire_anim(info);
	// update_animation(param);
	handle_arrow_fov(info);
	handle_ws_movements(info, info->mlx, tmp);
	handle_ad_movements(info, info->mlx, tmp);
}
