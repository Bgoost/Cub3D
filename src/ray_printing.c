/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_printing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:29:23 by martalop          #+#    #+#             */
/*   Updated: 2025/03/08 21:17:09 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	handle_y_texture(t_math_texture *t, mlx_texture_t *wall_texture)
{
	t->texture_in.y = (int)t->text_pos % wall_texture->height;
	if (t->texture_in.y < 0)
		t->texture_in.y += wall_texture->height;
	t->text_pos += t->step;
}

static void	print_wall(int x, int *y, t_game *info, t_math_texture *t)
{
	uint32_t		texture_color;

	if (info->ray->last_wall_pixel == WIN_HEIGHT - 1)
		info->ray->last_wall_pixel += 1;
	while (*y < info->ray->last_wall_pixel)
	{
		handle_y_texture(t, info->ray->wall_texture);
		texture_color = get_texture_pixel(info->ray->wall_texture,
				t->texture_in.x, t->texture_in.y);
		mlx_put_pixel(info->image, x, *y, texture_color);
		if (*y + 1 == info->ray->last_wall_pixel && *y + 1 != WIN_HEIGHT - 1)
			return ;
		*y += 1;
	}
}

static void	handle_xy_texture(t_math_texture *t, t_ray *ray)
{
	t->step = (double)ray->wall_texture->height / ray->projection_height;
	t->text_pos = (ray->first_wall_pixel - WIN_HEIGHT / 2
			+ ceil(ray->projection_height / 2)) * t->step;
	if (ray->wall_hit == 'v')
		t->texture_in.x = fmod(ray->hit_point->y, TILE);
	else
		t->texture_in.x = fmod(ray->hit_point->x, TILE);
	t->texture_in.x = (t->texture_in.x / TILE) * ray->wall_texture->width;
}

void	print_column(t_ray *ray, t_game *info, int x)
{
	int				y;
	t_math_texture	text_info;

	y = 0;
	ray->wall_texture = get_wall_texture(ray, info->textures);
	handle_xy_texture(&text_info, ray);
	while (y < WIN_HEIGHT)
	{
		if (y < ray->first_wall_pixel)
			mlx_put_pixel(info->image, x, y, info->ceiling_color);
		else if (y >= ray->first_wall_pixel && y < ray->last_wall_pixel)
			print_wall(x, &y, info, &text_info);
		else if (y < WIN_HEIGHT)
			mlx_put_pixel(info->image, x, y, info->floor_color);
		y++;
	}
}
