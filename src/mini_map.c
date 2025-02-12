#include "../inc/cub3d.h"

#define MINIMAP_SCALE 10
#define MINIMAP_X_OFFSET 10
#define MINIMAP_Y_OFFSET 10
#define PLAYER_COLOR 0xFF0000FF
#define TRANSPARENT 0xffffff00

static void paint_minimap(t_raycasting *info, int x, int y, int color)
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
            mlx_put_pixel(info->image, MINIMAP_X_OFFSET + (x * MINIMAP_SCALE) + map_x,
                            MINIMAP_Y_OFFSET + (y * MINIMAP_SCALE) + map_y, color);
            map_x++;
        }
        map_y++;
    }
}

static void draw_player(t_raycasting *info, mlx_image_t *image)
{
    int map_x;
    int map_y;
    int player_x;
    int player_y;

    player_y = MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE);
    player_x = MINIMAP_X_OFFSET + (info->player.x * MINIMAP_SCALE);

    map_x = 0;
    map_y = 0;
    while(map_y <= 5)
    {
        map_x = 0;
        while(map_x <= 5)
        {
            mlx_put_pixel(image, player_x + map_x, player_y + map_y, PLAYER_COLOR);
            map_x++;
        }
        map_y++;
    }
}

void draw_minimap(mlx_image_t *image, char **map, t_raycasting *info)
{
    int x;
    int y;
    int map_height;
    int map_width;
    int color;

    map_height = info->height;
    map_width = info->width;
    // Aqui le pasaremos el map->height y map->width cuando incorpuremos el parser
    y = 0;
    while(y < map_height)
    {
        x = 0;
        while(x < map_width)
        {
            if (map[y] == NULL || x >= (int)ft_strlen(map[y]))
                continue;

            // color = (map[y][x] == '1') ? WALL_COLOR : FLOOR_COLOR;
            if(map[y][x] == '1')
                color = WALL_COLOR;
            if(map[y][x] == '0')
                color = FLOOR_COLOR;
            else if(map[y][x] == ' ')
                color = TRANSPARENT;
            paint_minimap(info, x, y, color);
            x++;
        }
        y++;
    }
    printf("player x: %f, player y: %f\n", info->player.x, info->player.y);

    draw_player(info, image);
    printf("adios\n");
}