/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:34:09 by martalop          #+#    #+#             */
/*   Updated: 2025/03/08 21:17:25 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_wall(double x, double y, t_game *info)
{
	int	x_;
	int	y_;

	x_ = floor(x);
	y_ = floor(y);
	if (info->map[y_][x_] == '1')
		return (1);
	return (0);
}

// recibimos coordenadas en unidades de 1 x 1 pero con decimales (ej; (2'25, 5))
int	safe_map_point(double x, double y, int width, int height)
{
	if (x < 0 || ceil(x) >= width)
		return (0);
	if (y < 0 || ceil(y) >= height)
		return (0);
	return (1);
}

int	safe_hit_point(double x, double y, int width, int height)
{
	if ((int)x / TILE < 0 || ((int)x / TILE) >= width)
		return (0);
	if ((int)y / TILE < 0 || ((int)y / TILE) >= height)
		return (0);
	return (1);
}

double	degree_to_radian(double degree)
{
	double	radian;

	radian = (degree * M_PI) / (double)180.0;
	return (radian);
}

double	adjust_angle(double angle)
{
	double	res;

	res = 0;
	res = fmod(angle, 360.0);
	if (res <= 0.0)
		res = res + 360.0;
	return (res);
}
