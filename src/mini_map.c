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

int	ft_lstsize(t_sprite *lst)
{
    int	i;

    i = 0;
    if (!lst)
        return (0);
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}

void load_player_sprite(t_game *game)
{
    int i;
    game->anim.current_frame = 0;
    game->anim.sprites = NULL;
    mlx_texture_t *texture;
    char *sprite_paths[8] = {
        "sprites/anim/anim_1.png", "sprites/anim/anim_2.png", "sprites/anim/anim_3.png",
        "sprites/anim/anim_4.png", "sprites/anim/anim_5.png", "sprites/anim/anim_6.png",
        "sprites/anim/anim_7.png", "sprites/anim/anim_8.png"
    };
    
    i = 0;
    while(i < 8)
    {
        texture = mlx_load_png(sprite_paths[i]);
        if (!texture)
        {
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", sprite_paths[i]);
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

void draw_player_gun(t_game *game)
{
    int current_frame = game->anim.current_frame;
    int next_frame = (current_frame + 1) % 8;
    
    // Hide previous frame (don't delete it, just make it invisible)
    if (game->anim.player_sprites[current_frame])
        game->anim.player_sprites[current_frame]->enabled = false;

    // Show the next frame
    if (game->anim.player_sprites[next_frame])
    {
        game->anim.player_sprites[next_frame]->enabled = true;
        mlx_image_to_window(game->mlx, game->anim.player_sprites[next_frame], 0, 0);
    }
    
    game->anim.current_frame = next_frame;
}


void test_cursor(void *param)
{
    t_game	*info;

	info = (t_game *)param;
    if(mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT))
        printf("Mouse: 1\n");
    if(mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_RIGHT))
        printf("Mouse: 2\n");


}

void update_animation(t_anim *anim, double dt)
{
    if (anim) 
    {
        anim->accum += dt * 10000;
        if (anim->accum > anim->frame_speed)
        {
        anim->accum -= anim->frame_speed;
        anim->current_frame++;
        int size = ft_lstsize(anim->sprites);
        printf("size: %d\n", size);
        anim->current_frame %= ft_lstsize(anim->sprites);
        }
    }
}

void update(void * ptr)
{
    // t_game *game = (t_game*)ptr;
    (void)ptr;

    // draw_player_gun(game);
}

#define MINIMAP_RADIUS 7 

/*void	paint_minimap(t_game *game, int x, int y, int color)
{
    int map_x;
    int map_y;

    map_x = 0;
    map_y = 0;
	printf("x: %d\n", x);
	printf("y: %d\n", y);
    while(map_y < MINIMAP_SCALE)
    {
        map_x = 0;
        while(map_x < MINIMAP_SCALE)
        {

            int tmp_x = MINIMAP_X_OFFSET + (x * MINIMAP_SCALE) + map_x;
            int tmp_y = MINIMAP_Y_OFFSET + (y * MINIMAP_SCALE) + map_y;
//        	printf("tmp_x: %d, tmp_y = %d\n", tmp_x, tmp_y);
            mlx_put_pixel(game->image, tmp_x,
                            tmp_y, color);
            map_x++;
        }
        map_y++;
    }
}*/





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

	/*
static void draw_player_pixel(t_game *game, mlx_image_t *image)
{
    double center_x;
    double center_y;
    double map_x;
    double map_y;

    center_y = MINIMAP_Y_OFFSET + ((game->player.y - game->player.y) + MINIMAP_RADIUS) * MINIMAP_SCALE;
    center_x = MINIMAP_X_OFFSET + ((game->player.x - game->player.x) + MINIMAP_RADIUS) * MINIMAP_SCALE;
    printf("player x: %f, player y: %f\n", game->player.x, game->player.y);
    printf("center x: %f, center y: %f\n", center_x, center_y);

    if(center_x < 90.0)
        center_x = 90.0;
    if(center_y > 80.0)
        center_y = 80.0;
    printf("------ center x: %f, center y: %f\n", center_x, center_y);


    while (map_y <= 2)
    {
        map_x = -2.0;
        while (map_x <= 2.0)
        {
			printf("pixel x = %d, pixel y = %d\n", (int)(center_x + map_x), (int)(center_y + map_y));
            mlx_put_pixel(image, (int)(center_x + map_x), (int)(center_y + map_y), PLAYER_COLOR);
            map_x++;
        }
        map_y++;
    }
}*/


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
/*
void draw_minimap(mlx_image_t *image, char **map, t_game *game)
{
	(void)map;
    int x, y;
	int color;
    double player_x = game->player.x;
    double player_y = game->player.y;

    y = -MINIMAP_RADIUS;
    while (y <= MINIMAP_RADIUS)
    {
        x = -MINIMAP_RADIUS;
        while (x <= MINIMAP_RADIUS)
        {
            int map_x = (int)floor(player_x + x);
            int map_y = (int)floor(player_y + y);
			printf("map_x = %d map_y = %d\n", map_x, map_y);
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
		   paint_minimap(game, color);
		   x++;
        }
        y++;
    }
    draw_player_pixel(game, image);
}*/


// static void paint_minimap(t_game *game, int x, int y, int color)
// {
//     int map_x;
//     int map_y;

//     map_x = 0;
//     map_y = 0;
//     while(map_y < MINIMAP_SCALE)
//     {
//         map_x = 0;
//         while(map_x < MINIMAP_SCALE)
//         {

//             int tmp_x = MINIMAP_X_OFFSET + (x * MINIMAP_SCALE) + map_x;
//             int tmp_y = MINIMAP_Y_OFFSET + (y * MINIMAP_SCALE) + map_y;
//             mlx_put_pixel(game->image, tmp_x,
//                             tmp_y, color);
//             map_x++;
//         }
//         map_y++;
//     }
// }

// static void draw_player_pixel(t_game *info, mlx_image_t *image)
// {
//     int map_x;
//     int map_y;
//     int player_x;
//     int player_y;

//     player_y = MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE);
//     player_x = MINIMAP_X_OFFSET + (info->player.x * MINIMAP_SCALE);

//     map_x = 0;
//     map_y = 0;
//     while(map_y <= 1)
//     {
//         map_x = 0;
//         while(map_x <= 1)
//         {
//             mlx_put_pixel(image, player_x + map_x, player_y + map_y, PLAYER_COLOR);
//             map_x++;
//         }
//         map_y++;
//     }
// }

// void draw_minimap(mlx_image_t *image, char **map, t_game *game)
// {
//     int x;
//     int y;
//     int map_height;
//     int map_width;
//     int color;
//     (void)image;

// 	color = 0;
//     map_height = game->map_height;
//     map_width = game->map_width;
//     // Aqui le pasaremos el map->height y map->width cuando incorpuremos el parser
//     y = 0;
//     while(y < map_height)
//     {
//         x = 0;
//         while(x < map_width)
//         {
//             if (map[y] == NULL || x >= (int)ft_strlen(map[y]))
//                 continue;
//             if(map[y][x] == '1')
//                 color = WALL_COLOR;
//             if(map[y][x] == '0')
//                 color = FLOOR_COLOR;
//             else if(map[y][x] == ' ')
//                 color = TRANSPARENT;
//             paint_minimap(game, x, y, color);
//             x++;
//         }
//         y++;
//     }
// 	// animation_loop2(game);
//     draw_player_pixel(game, image);
// }
