#include "../inc/cub3d.h"
#include <sys/time.h>
#define MINIMAP_SCALE 10
#define MINIMAP_X_OFFSET 10
#define MINIMAP_Y_OFFSET 10
#define PLAYER_COLOR 0xFF0000FF
#define TRANSPARENT 0xffffff00
#define WALLCOLOR 0xffffff00
#define FLOORCOLOR 0xffffff00

t_sprite	*ft_lstnew(void *sprite)
{
	t_sprite	*new;

	new = (t_sprite *)malloc(sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->sprite = (void *)sprite;
	new->next = NULL;
	return (new);
}

t_sprite *ft_lstlast(t_sprite *lst)
{
    if (!lst) // Avoid NULL dereference
        return (NULL);
    while (lst->next)
    {
        lst = lst->next;
    }
    return (lst);
}


void	ft_spriteadd_back(t_sprite **lst, t_sprite *new)
{
    t_sprite	*tmp;

    if (!new)
        return;
    if (!*lst)  // If the list is empty, set new as the first element
    {
        *lst = new;
        return;
    }
    tmp = ft_lstlast(*lst);
    if (!tmp)  // Safety check to prevent dereferencing NULL
        return;
    tmp->next = new;
}


void load_player_sprite(t_game *game)
{
    int i;
    game->anim.current_frame = 0;
    game->anim.frame_counter = 0;
    game->anim.frame_speed = 10000000;
    game->anim.sprites = NULL;  // Ensure it's properly initialized
    mlx_texture_t *texture;
    mlx_image_t* frame;
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
        frame = mlx_new_image(game->mlx, MINIMAP_Y_OFFSET + (game->player.x * MINIMAP_SCALE), 
                              MINIMAP_Y_OFFSET + (game->player.y * MINIMAP_SCALE));
        
        t_sprite *new_sprite = ft_lstnew(frame);
        if (!new_sprite) 
        {
            printf("\033[31mError:\nMemory allocation failed for new sprite node\033[0m\n");
            exit_error("");
        }
        
        ft_spriteadd_back(&game->anim.sprites, new_sprite);
        mlx_delete_texture(texture);
        i++;
    }
}

static int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


int32_t mlx_get_pixel(mlx_image_t* image, uint32_t x, uint32_t y) 
{
    if (x > image->width || y > image->height)
      return 0xFF000000;
    uint8_t* pixelstart = image->pixels + (y * image->width + x) * 4;
    return get_rgba(*(pixelstart), *(pixelstart + 1),
      * (pixelstart + 2), *(pixelstart + 3));
}

void draw_player(t_game *game)
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

    int player_x = MINIMAP_X_OFFSET + (game->player.x * MINIMAP_SCALE);
    int player_y = MINIMAP_Y_OFFSET + (game->player.y * MINIMAP_SCALE);

    mlx_image_to_window(game->mlx, new_sprite, player_x, player_y);

    game->anim.current_frame = next_frame;
}
void  put_img_to_img(t_game *game, mlx_image_t *frame) 
{
    int i;
    int j;
    int player_x = MINIMAP_X_OFFSET + (game->player.x * MINIMAP_SCALE);
    int player_y = MINIMAP_Y_OFFSET + (game->player.y * MINIMAP_SCALE);
    i = 0;
    while(i < 64) {
      j = 0;
      while (j < 64) {
        printf("i: %d, j: %d\n", i, j);
        printf("player_x: %d, player_y: %d\n", player_x, player_y);
          mlx_put_pixel(frame, 0, 0, mlx_get_pixel(frame, i, j));
        j++;
      }
      i++;
    }
    if (mlx_image_to_window(game->mlx, frame, 0, 0) < 0)
        exit_error("Failed to put image to window");
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

  t_sprite	*ft_lstget(t_sprite *l, int n)
  {
      while (n-- && l)
          l = l->next;
      return (l);
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
        anim->current_frame %= ft_lstsize(anim->sprites);
      }
    }
  }

void update(void * ptr)
{
    t_game *game = (t_game*)ptr;

    mlx_image_t *frame = (mlx_image_t *)ft_lstget(game->anim.sprites, game->anim.current_frame)->sprite;
    if (!frame)
        exit(1);
    printf("frame: %p\n", frame);
    // put_img_to_img(game, frame);
    draw_player(game);
    update_animation(&game->anim, game->mlx->delta_time);
}

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

static void draw_player_pixel(t_game *info, mlx_image_t *image)
{
    int map_x;
    int map_y;
    int player_x;
    int player_y;

    player_y = MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE);
    player_x = MINIMAP_X_OFFSET + (info->player.x * MINIMAP_SCALE);

    map_x = 0;
    map_y = 0;
    while(map_y <= 1)
    {
        map_x = 0;
        while(map_x <= 1)
        {
            mlx_put_pixel(image, player_x + map_x, player_y + map_y, PLAYER_COLOR);
            map_x++;
        }
        map_y++;
    }
}

void draw_minimap(mlx_image_t *image, char **map, t_game *game)
{
    int x;
    int y;
    int map_height;
    int map_width;
    int color;
    (void)image;

	color = 0;
    map_height = game->map_height;
    map_width = game->map_width;
    // Aqui le pasaremos el map->height y map->width cuando incorpuremos el parser
    y = 0;
    while(y < map_height)
    {
        x = 0;
        while(x < map_width)
        {
            if (map[y] == NULL || x >= (int)ft_strlen(map[y]))
                continue;
            if(map[y][x] == '1')
                color = WALL_COLOR;
            if(map[y][x] == '0')
                color = FLOOR_COLOR;
            else if(map[y][x] == ' ')
                color = TRANSPARENT;
            paint_minimap(game, x, y, color);
            x++;
        }
        y++;
    }
	// animation_loop2(game);
    draw_player_pixel(game, image);
}
