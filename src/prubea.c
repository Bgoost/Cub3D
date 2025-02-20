/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgaratej <cgaratej@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:01:41 by cgaratej          #+#    #+#             */
/*   Updated: 2024/12/20 17:11:02 by cgaratej         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_animation(t_game *game)
{
	static long long	last_time = 0;
	long long			current_time;

	current_time = timestamp();
	if ((current_time - last_time) > game->anim.time)
	{
		game->anim.index++;
		if (game->anim.index > 7)
			game->anim.index = 0;
		last_time = current_time;
	}
}

void	draw_animation(t_game *game)
{
	if (game->anim.curren_img)
		mlx_delete_image(game->mlx, game->anim.curren_img);
	else if (game->anim.index == 1)
		draw_animation_pixel(game, game->anim.frame1);
	else if (game->anim.index == 2)
		draw_animation_pixel(game, game->anim.frame2);
	else if (game->anim.index == 3)
		draw_animation_pixel(game, game->anim.frame3);
	else if (game->anim.index == 4)
		draw_animation_pixel(game, game->anim.frame4);
	else if (game->anim.index == 5)
		draw_animation_pixel(game, game->anim.frame5);
	else if (game->anim.index == 6)
		draw_animation_pixel(game, game->anim.frame6);
	else if (game->anim.index == 7)
		draw_animation_pixel(game, game->anim.frame7);
    else if (game->anim.index == 8)
		draw_animation_pixel(game, game->anim.frame8);
    else if (game->anim.index == 9)
		draw_animation_pixel(game, game->anim.frame9);
}

void	init_anim(t_game *game)
{
	game->anim.frame1 = mlx_load_png("./assets/animation/frame1.png");
	game->anim.frame2 = mlx_load_png("./assets/animation/frame2.png");
	game->anim.frame3 = mlx_load_png("./assets/animation/frame3.png");
	game->anim.frame4 = mlx_load_png("./assets/animation/frame4.png");
	game->anim.frame5 = mlx_load_png("./assets/animation/frame5.png");
	game->anim.frame6 = mlx_load_png("./assets/animation/frame6.png");
	game->anim.frame7 = mlx_load_png("./assets/animation/frame7.png");
	game->anim.frame8 = mlx_load_png("./assets/animation/frame8.png");
	game->anim.frame9 = mlx_load_png("./assets/animation/frame9.png");
	game->anim.index = 0;
	game->anim.time = 100;
}

void	animation_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	update_animation(game);
	draw_animation(game);
}

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int32_t	mlx_get_pixel_png(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * 4;
	return (get_rgba(*(pixelstart), *(pixelstart + 1), \
					*(pixelstart + 2), *(pixelstart + 3)));
}

void	draw_animation_pixel(t_game *game, mlx_texture_t *texture)
{
	int	i;
	int	j;

	game->anim.curren_img = mlx_texture_to_image(game->mlx, texture);
	if (!game->anim.curren_img)
	{
		err_msg("Animation", "Failed to create temp image", 1);
		return ;
	}
	i = 0;
	while (i < 37)
	{
		j = 0;
		while (j < 37)
		{
			mlx_put_pixel(game->anim.curren_img, i, j, \
								mlx_get_pixel_png(game->anim.curren_img, i, j));
			j++;
		}
		i++;
	}
	mlx_image_to_window(game->mlx, game->anim.curren_img, WIDTH - 50, 20);
}