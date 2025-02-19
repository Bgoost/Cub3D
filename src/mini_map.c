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

t_sprite	*ft_lstlast(t_sprite *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_spriteadd_back(t_sprite **lst, t_sprite *new)
{
	t_sprite	*tmp;

	if (!*lst)
		*lst = new;
	else if (lst && new)
	{
		tmp = ft_lstlast(*lst);
		tmp->next = new;
	}
}

void load_player_sprite(t_raycasting *info)
{
    int i;
    info->anim.current_frame = 0;
    info->anim.frame_counter = 0;
    mlx_texture_t *texture;
    mlx_image_t* frame;
    char *sprite_paths[9] = {
        "sprites/anim/sprite_01.png", "sprites/anim/sprite_02.png", "sprites/anim/sprite_03.png",
        "sprites/anim/sprite_04.png", "sprites/anim/sprite_05.png", "sprites/anim/sprite_06.png",
        "sprites/anim/sprite_07.png", "sprites/anim/sprite_08.png", "sprites/anim/sprite_09.png"
    };
    
    i = 0;
    while(i < 9)
    {
        texture = mlx_load_png(sprite_paths[i]);
        if (!texture)
        {
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m", sprite_paths[i]);
            exit_error("");
        }
        info->anim.player_sprites[i] = mlx_texture_to_image(info->mlx, texture);
        if (!info->anim.player_sprites[i])
        {
            printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m", i);
            exit_error("");
        }
        frame = mlx_new_image(info->mlx, MINIMAP_Y_OFFSET + (info->player.x * MINIMAP_SCALE), MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE));
        ft_spriteadd_back(&info->anim.sprites, ft_lstnew(frame));
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

void draw_player(t_raycasting *info)
{
    int next_frame;
    mlx_image_t *new_sprite;
    
    next_frame = (info->anim.current_frame + 1) % 9;
    new_sprite = info->anim.player_sprites[next_frame];
    if (!new_sprite)
    {
        printf("\033[31mError: Player sprite at frame %d is NULL\033[0m\n", next_frame);
        return;
    }

    int player_x = MINIMAP_X_OFFSET + (info->player.x * MINIMAP_SCALE);
    int player_y = MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE);

    mlx_image_to_window(info->mlx, new_sprite, player_x, player_y);

    info->anim.current_frame = next_frame;
}
void  put_img_to_img(t_raycasting *info) 
{
    int i;
    int j;
    int player_x = MINIMAP_X_OFFSET + (info->player.x * MINIMAP_SCALE);
    int player_y = MINIMAP_Y_OFFSET + (info->player.y * MINIMAP_SCALE);
    i = 0;
    while(i < info->width) {
      j = 0;
      while (j < info->height) {
          mlx_put_pixel(info->image, player_x + i, player_y + j, mlx_get_pixel(info->image, i, j));
        j++;
      }
      i++;
    }
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
      anim->accum += dt * 1000;
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
    t_raycasting *info = (t_raycasting*)ptr;

    mlx_image_t *frame = (mlx_image_t *)ft_lstget(info->anim.sprites, info->anim.current_frame)->sprite;
    if (!frame)
        exit(1);
    put_img_to_img(info);
    update_animation(&info->anim, info->mlx->delta_time);
}

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

void draw_minimap(mlx_image_t *image, char **map, t_raycasting *info)
{
    int x;
    int y;
    int map_height;
    int map_width;
    int color;
    (void)image;

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
            if(map[y][x] == '1')
                color = WALLCOLOR;
            if(map[y][x] == '0')
                color = FLOORCOLOR;
            else if(map[y][x] == ' ')
                color = TRANSPARENT;
            paint_minimap(info, x, y, color);
            x++;
        }
        y++;
    }
	// animation_loop2(info);

}