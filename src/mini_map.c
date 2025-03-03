/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 20:13:55 by martalop          #+#    #+#             */
/*   Updated: 2025/03/02 20:36:26 by martalop         ###   ########.fr       */
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

#define MINI_PLAYER_HEIGHT 6
#define MINI_PLAYER_WIDTH 6

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
	//while (sprite_paths[i])
    while(i < 8)
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
}*/

void	print_mini_ray(t_game *game, t_point ray_dir, t_point ray_pos, char **map)
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

void	print_mini_ray(t_game *game, t_point ray_dir, t_point ray_pos, char **map)
{
	(void)map;
	int		mini_x;
	int		mini_y;
	int		hit;
    double	step_size = 0.05; // Step size for the ray (smaller = more precise)

	hit = 0;
    while (!hit) 
	{
        ray_pos.x += ray_dir.x * step_size;
	 //	printf("ray_pos_x = %f, ray_pos_y = %f\n", ray_pos.x, ray_pos.y);
        if (!safe_map_point(ray_pos.x, ray_pos.y, game->map_width, game->map_height) || is_wall(ray_pos.x, ray_pos.y, game)) 
			hit = 1;
		
        ray_pos.y += ray_dir.y * step_size;
        if (!safe_map_point(ray_pos.x, ray_pos.y, game->map_width, game->map_height) || is_wall(ray_pos.x, ray_pos.y, game)) 
			hit = 1;
		// Scale the ray's position to minimap coordinates
		mini_x = (ray_pos.x - (game->player.x - MINIMAP_SCALE / 2)) * (MINIMAP_SIZE / MINIMAP_SCALE);
		mini_y = (ray_pos.y - (game->player.y - MINIMAP_SCALE / 2)) * (MINIMAP_SIZE / MINIMAP_SCALE);
        
		// Check if the ray is within the minimap's bounds
        if (mini_x < 0 || mini_x >= MINIMAP_SIZE || mini_y < 0 || mini_y >= MINIMAP_SIZE)
            break ; // Stop drawing if the ray goes outside the minimap
		mlx_put_pixel(game->image, mini_x + MINIMAP_X_OFFSET, mini_y + MINIMAP_Y_OFFSET , RAY_COLOR);
    }
}

void	draw_minimap_ray(mlx_image_t *image, t_game *game, char **map) 
{
	(void)image;
    t_point ray_pos;
    t_point ray_dir;
	double	angle;
	int	i;
	double	increment;

	i = 0;
    ray_pos.x = game->player.x;
    ray_pos.y = game->player.y;
//	printf("pos.x = %f, pos.y = %f\n", ray_pos.x, ray_pos.y);
	angle = game->direction + (FOV /2);
	increment = (double)FOV / (double)WIN_WIDTH;
	while (i < WIN_WIDTH)
	{
		angle = adjust_angle(angle);
	//	printf("angle = %f\n", angle);
		ray_dir.x = cos(degree_to_radian(angle));
		ray_dir.y = -sin(degree_to_radian(angle)); 
	 //	printf("ray_dir_x = %f, ray_dir_y = %f\n", ray_dir_x, ray_dir_y);
		print_mini_ray(game, ray_dir, ray_pos, map);
		angle = angle - increment;
		i++;
	}
//	printf("direction = %f\n", game->direction);
//	printf("end angle = %f\n", adjust_angle(game->direction - (FOV / 2)));
//	printf("I exit loop at angle = %f\n", angle);
//	printf("i = %d\n", i);
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
//			printf("printing player at x = %d, y = %d\n", (int)mini_player_pos.x + player_x + MINIMAP_X_OFFSET, (int)mini_player_pos.y + player_y + MINIMAP_Y_OFFSET);
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
    draw_minimap_ray(image, game, game->map);
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
