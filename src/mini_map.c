/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:13:55 by martalop          #+#    #+#             */
/*   Updated: 2025/02/26 21:26:24 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <sys/time.h>
// movimiento para que el minimapa para que no esté pegado a la esquina
#define MINIMAP_X_OFFSET 10
#define MINIMAP_Y_OFFSET 10

// Tamaño del minimapa (no en pixeles)
// cuanto de el mapa real puedes ver en el minimapa.
#define MINIMAP_SCALE 10.0

//Tamaño real del minimapa(en pixeles)
#define MINIMAP_SIZE 200.0

#define MINI_PLAYER_HEIGHT 5
#define MINI_PLAYER_WIDTH 5

#define PLAYER_COLOR 0xFF0000FF
#define TRANSPARENT 0xffffff00
#define WALLCOLOR 0xffffff00 
#define FLOORCOLOR 0xffffff00


void load_player_sprite(t_game *game)
{
    int i;
    game->anim.current_frame = 0;
    game->anim.is_animating = false;
    game->anim.sprites = NULL;
    for (int j = 0; j < 5; j++)
    {
        game->anim.player_sprites[j] = NULL;
    }
    mlx_texture_t *texture;
    game->anim.sprite_paths[0] = "sprites/anim/anim_1.png";
    game->anim.sprite_paths[1] = "sprites/anim/anim_2.png";
    game->anim.sprite_paths[2] = "sprites/anim/anim_3.png";
    game->anim.sprite_paths[3] = "sprites/anim/anim_4.png";
    game->anim.sprite_paths[4] = "sprites/anim/anim_5.png";
    
    
    i = 0;
    while(i < 5)
    {
        texture = mlx_load_png(game->anim.sprite_paths[i]);
        if (!texture)
        {
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", game->anim.sprite_paths[i]);
            exit_error("");
        }
        game->anim.player_sprites[i] = mlx_texture_to_image(game->mlx, texture);
        if (!game->anim.player_sprites[i])
        {
            printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m\n", i);
            exit_error("");
        }
        mlx_delete_texture(texture);
        i++;
    }
}


void update_animation(void *param)
{
    t_game *game = (t_game *)param;
    if (!game->anim.is_animating)
        return;

    double current_time = mlx_get_time();
    if (current_time - game->anim.last_frame_time < 0.05)
        return;

    game->anim.last_frame_time = current_time;
    int current_frame = game->anim.current_frame;
    int next_frame = current_frame + 1;

    // Delete current image before replacing it
    if (game->anim.player_sprites[current_frame])
    {
        mlx_delete_image(game->mlx, game->anim.player_sprites[current_frame]);
        game->anim.player_sprites[current_frame] = NULL; // Avoid dangling pointer
    }

    if (next_frame < 5)
    {
        // Load and convert next frame
        mlx_texture_t *texture = mlx_load_png(game->anim.sprite_paths[next_frame]);
        if (!texture)
        {
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", game->anim.sprite_paths[next_frame]);
            exit_error("");
        }

        game->anim.player_sprites[next_frame] = mlx_texture_to_image(game->mlx, texture);
        if (!game->anim.player_sprites[next_frame])
        {
            printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m\n", next_frame);
            exit_error("");
        }

        // Free texture after conversion
        mlx_delete_texture(texture);

        // Add the new frame to the window
        mlx_image_to_window(game->mlx, game->anim.player_sprites[next_frame], 0, 0);
        game->anim.current_frame = next_frame;
    }
    else
    {
        game->anim.is_animating = false;
    }
}



void test_cursor(void *param)
{
    t_game	*info;

	info = (t_game *)param;
    if(mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT) && !info->anim.is_animating)
    {
        info->anim.is_animating = true;
        info->anim.current_frame = 0;
        info->anim.last_frame_time = mlx_get_time(); 
    }
}

static void draw_player_pixel(mlx_image_t *image)
{
	t_point	mini_player_pos;
    int player_x;
    int player_y;

    player_y = -MINI_PLAYER_HEIGHT / 2;
	mini_player_pos.x = MINIMAP_SIZE / 2;
	mini_player_pos.y = MINIMAP_SIZE / 2;
	while (player_y < MINI_PLAYER_HEIGHT / 2)
	{
    	player_x = -MINI_PLAYER_WIDTH / 2;
		while (player_x < MINI_PLAYER_WIDTH / 2)
		{
			mlx_put_pixel(image, mini_player_pos.x + player_x + MINIMAP_X_OFFSET, mini_player_pos.y + player_y + MINIMAP_Y_OFFSET, PLAYER_COLOR);
			player_x++;
		}
		player_y++;
	}
}

int	get_color(t_point minimap_pos, t_game *game, char **map)
{
	int color;
	int map_x;
	int map_y; 
   
	map_x = floor(minimap_pos.x);
	map_y = floor(minimap_pos.y);
//	printf("map_x = %d map_y = %d\n", map_x, map_y);
	if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
	{
		//	printf("printing transparent(%x)\n", TRANSPARENT);
		color = TRANSPARENT;
	}
	else if (map[map_y][map_x] == '1')
	{
		//	printf("printing wall(%x)\n", WALL_COLOR);
		color = WALL_COLOR;
	}
	else if (map[map_y][map_x] == '0')
	{
		//	printf("printing floor(%x)\n", FLOOR_COLOR);
		color = FLOOR_COLOR;
	}
	else
	{
		//	printf("printing transparent(%x)\n", TRANSPARENT);
		color = TRANSPARENT;
	}
	return (color);
}

void draw_minimap(mlx_image_t *image, char **map, t_game *game)
{
	t_point	minimap_start;
	t_point	position;
	int	x;
	int	y;
	int color;

//	ft_putstr_fd("map rerender\n", 2);
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
            mlx_put_pixel(game->image, x + MINIMAP_X_OFFSET, y + MINIMAP_Y_OFFSET, color);
			x++;
		}
		y++;
	}
	draw_player_pixel(image);
}