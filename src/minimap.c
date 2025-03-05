/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:13:55 by martalop          #+#    #+#             */
/*   Updated: 2025/03/05 16:53:24 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
