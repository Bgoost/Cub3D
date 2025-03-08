/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:26:13 by martalop          #+#    #+#             */
/*   Updated: 2025/03/08 21:16:37 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	adjust_pixels(int *first_wall_pixel, int *last_wall_pixel)
{
	int	tmp;

	tmp = 0;
	if (*last_wall_pixel > WIN_HEIGHT - 1)
	{
		tmp = *last_wall_pixel - (WIN_HEIGHT - 1);
		*last_wall_pixel = *last_wall_pixel - tmp;
	}
	if (*first_wall_pixel < 0)
	{
		tmp = *first_wall_pixel * (-1);
		*first_wall_pixel = *first_wall_pixel + tmp;
	}
}

uint32_t	get_ceiling_color(int *ceiling_color)
{
	uint8_t	rgba[4];
	int		i;

	i = 0;
	while (i < 3)
	{
		rgba[i] = ceiling_color[i];
		i++;
	}
	rgba[i] = 255;
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
}

uint32_t	get_floor_color(int *floor_color)
{
	uint8_t	rgba[4];
	int		i;

	i = 0;
	while (i < 3)
	{
		rgba[i] = floor_color[i];
		i++;
	}
	rgba[i] = 255;
	return (rgba[0] << 24 | rgba[1] << 16 | rgba[2] << 8 | rgba[3]);
}

uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int		pixel_index;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0x00000000);
	pixel_index = (y * texture->width + x) * texture->bytes_per_pixel;
	r = texture->pixels[pixel_index];
	g = texture->pixels[pixel_index + 1];
	b = texture->pixels[pixel_index + 2];
	a = texture->pixels[pixel_index + 3];
	if (a != 255)
	{
		r = (r * a) / 255;
		g = (g * a) / 255;
		b = (b * a) / 255;
	}
	return (r << 24 | g << 16 | b << 8 | a);
}

mlx_texture_t	*get_wall_texture(t_ray *ray, t_mlx_textures *textures)
{
	if ((ray->angle >= 270 || ray->angle < 90) && ray->wall_hit == 'v')
		return (textures->west);
	else if ((ray->angle < 270 && ray->angle >= 90) && ray->wall_hit == 'v')
		return (textures->east);
	else if ((ray->angle >= 0 && ray->angle <= 180) && ray->wall_hit == 'h')
		return (textures->south);
	else if ((ray->angle < 360 && ray->angle > 180) && ray->wall_hit == 'h')
		return (textures->north);
	return (NULL);
}
