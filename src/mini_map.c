#include "../inc/cub3d.h"
#include <sys/time.h>
#define MINIMAP_SCALE 10
#define MINIMAP_X_OFFSET 10
#define MINIMAP_Y_OFFSET 10
#define PLAYER_COLOR 0xFF0000FF
#define TRANSPARENT 0xffffff00
#define WALLCOLOR 0xffffff00
#define FLOORCOLOR 0xffffff00

void load_player_sprite(t_game *game)
{
    int i;
    game->anim.current_frame = 0;
    game->anim.frame_counter = 0;
    game->anim.frame_speed = 10000000;
    game->anim.sprites = NULL;
    mlx_texture_t *texture;
    char *sprite_paths[10] = {
        "sprites/anim/sprite_01.png", "sprites/anim/sprite_02.png", "sprites/anim/sprite_03.png",
        "sprites/anim/sprite_04.png", "sprites/anim/sprite_05.png", "sprites/anim/sprite_06.png",
        "sprites/anim/sprite_07.png", "sprites/anim/sprite_08.png", "sprites/anim/sprite_09.png",
        "sprites/anim/sprite_10.png"
    };
    
    i = 0;
    while(i < 10)
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
    int next_frame;
    mlx_image_t *new_sprite;
    
    next_frame = (game->anim.current_frame + 1) % 10;
    new_sprite = game->anim.player_sprites[next_frame];
    if (!new_sprite)
    {
        printf("\033[31mError: Player sprite at frame %d is NULL\033[0m\n", next_frame);
        return;
    }

    mlx_image_to_window(game->mlx, new_sprite, WIN_WIDTH / 2, WIN_HEIGHT - new_sprite->height);

    game->anim.current_frame = next_frame;
}

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
    t_game *game = (t_game*)ptr;

    // draw_player_gun(game);
    update_animation(&game->anim, game->mlx->delta_time);
}

#define MINIMAP_RADIUS 7 

static void paint_minimap(t_game *game, int x, int y, int color)
{
    int map_x;
    int map_y;

    map_x = 0;
    map_y = 0;
    while(map_y < MINIMAP_SCALE)
    {
        map_x = 0;
        while(map_x < MINIMAP_SCALE)
        {

            int tmp_x = MINIMAP_X_OFFSET + (x * MINIMAP_SCALE) + map_x;
            int tmp_y = MINIMAP_Y_OFFSET + (y * MINIMAP_SCALE) + map_y;
            mlx_put_pixel(game->image, tmp_x,
                            tmp_y, color);
            map_x++;
        }
        map_y++;
    }
}

static void draw_player_pixel(t_game *game, mlx_image_t *image)
{
    double center_x;
    double center_y;
    int map_x;
    int map_y;

    map_x = -2;
    map_y = -2;
    center_y = MINIMAP_Y_OFFSET + ((game->player.y - (int)game->player.y) + MINIMAP_RADIUS) * MINIMAP_SCALE;
    center_x = MINIMAP_X_OFFSET + ((game->player.x - (int)game->player.x) + MINIMAP_RADIUS) * MINIMAP_SCALE;
    printf("player x: %f, player y: %f\n", game->player.x, game->player.y);
    printf("center x: %f, center y: %f\n", center_x, center_y);
    if(center_x < 90.0)
        center_x = 90.0;
    if(center_y > 80.0)
        center_y = 80.0;
    printf("------ center x: %f, center y: %f\n", center_x, center_y);

    while (map_y <= 2)
    {
        map_x = -2;
        while (map_x <= 2)
        {
            mlx_put_pixel(image, (int)(center_x + map_x), (int)(center_y + map_y), PLAYER_COLOR);
            map_x++;
        }
        map_y++;
    }
}

void draw_minimap(mlx_image_t *image, char **map, t_game *game)
{
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
            int map_x = (int)(player_x + x);
            int map_y = (int)(player_y + y);
            if (map_y < 0 || map_y >= game->map_height || map_x < 0 || map_x >= game->map_width)
                color = TRANSPARENT;
            else if (map[map_y][map_x] == '1')
                color = WALL_COLOR;
            else if (map[map_y][map_x] == '0')
                color = FLOOR_COLOR;
            else
                color = TRANSPARENT;

            paint_minimap(game, (x + MINIMAP_RADIUS), (y + MINIMAP_RADIUS), color);
            x++;
        }
        y++;
    }
    draw_player_pixel(game, image);
}


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