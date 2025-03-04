/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:13:55 by martalop          #+#    #+#             */
/*   Updated: 2025/03/04 02:00:27 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
// movimiento para que el minimapa para que no esté pegado a la esquina
#define MINIMAP_X_OFFSET 10
#define MINIMAP_Y_OFFSET 10

// Tamaño del minimapa (no en pixeles)
// cuanto de el mapa real puedes ver en el minimapa.
#define MINIMAP_SCALE 10.0

//Tamaño real del minimapa(en pixeles)
#define MINIMAP_SIZE 200.0

#define MINI_PLAYER_HEIGHT 8
#define MINI_PLAYER_WIDTH 8

#define PLAYER_COLOR 0xFF0000FF
#define TRANSPARENT 0x1c2d36FF
#define WALLCOLOR 0xffffff00
#define FLOORCOLOR 0xffffff00
#define RAY_COLOR 0x4A001FFF

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

static void	draw_player_pixel(mlx_image_t *image)
{
	t_point	mini_player_pos;
	int		player_x;
	int		player_y;
	int		x;
	int		y;

	player_y = -MINI_PLAYER_HEIGHT / 2;
	mini_player_pos.x = MINIMAP_SIZE / 2;
	mini_player_pos.y = MINIMAP_SIZE / 2;
	while (player_y < MINI_PLAYER_HEIGHT / 2)
	{
		player_x = -MINI_PLAYER_WIDTH / 2;
		while (player_x < MINI_PLAYER_WIDTH / 2)
		{
			x = mini_player_pos.x + player_x + MINIMAP_X_OFFSET;
			y = mini_player_pos.y + player_y + MINIMAP_Y_OFFSET;
			mlx_put_pixel(image, x, y, PLAYER_COLOR);
			player_x++;
		}
		player_y++;
	}
}

int	get_color(t_point minimap_pos, t_game *game, char **map)
{
	int	color;
	int	map_x;
	int	map_y;

	map_x = floor(minimap_pos.x);
	map_y = floor(minimap_pos.y);
	if (map_y < 0 || map_y >= game->map_height
		|| map_x < 0 || map_x >= game->map_width)
		color = TRANSPARENT;
	else if (map[map_y][map_x] == '1')
		color = 0x007EA7FF;
	else if (map[map_y][map_x] == '0')
		color = 0xB4DFF8FF;
	else
		color = TRANSPARENT;
	return (color);
}

void	draw_minimap(mlx_image_t *image, char **map, t_game *game)
{
	t_point	minimap_start;
	t_point	position;
	int		x;
	int		y;
	int		color;

	minimap_start.x = game->player.x - MINIMAP_SCALE / 2;
	minimap_start.y = game->player.y - MINIMAP_SCALE / 2;
	y = 0;
	while (y < MINIMAP_SIZE)
	{
		x = 0;
		while (x < MINIMAP_SIZE)
		{
			position.x = minimap_start.x + (MINIMAP_SCALE * x / MINIMAP_SIZE);
			position.y = minimap_start.y + (MINIMAP_SCALE * y / MINIMAP_SIZE);
			color = get_color(position, game, map);
			mlx_put_pixel(game->image, x + MINIMAP_X_OFFSET,
				y + MINIMAP_Y_OFFSET, color);
			x++;
		}
		y++;
	}
	draw_player_pixel(image);
	draw_minimap_rays(game);
}
