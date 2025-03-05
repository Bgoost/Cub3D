#include "../inc/cub3d.h"

t_anim *init_anim(void)
{
    t_anim *anim;
    int i;

    i = 0;
    anim = (t_anim *)malloc(sizeof(t_anim));
    if (!anim)
        return (NULL);
    anim->is_animating = 0;
    anim->last_frame_time = 0.0;
    anim->current_frame = 0;
    while(i < 6)
        anim->player_sprites[i++] = NULL;
    while(i < 12)
        anim->sprite_paths[i++ - 6] = NULL;
    while(i < 18)
        anim->player_texture[i++ - 12] = NULL;
    return (anim);
}
void init_and_set(t_game *game)
{
    int             i;

    game->anim->sprite_paths[0] = ft_strdup("sprites/anim/anim_1.png");
    game->anim->sprite_paths[1] = ft_strdup("sprites/anim/anim_2.png");
    game->anim->sprite_paths[2] = ft_strdup("sprites/anim/anim_3.png");
    game->anim->sprite_paths[3] = ft_strdup("sprites/anim/anim_4.png");
    game->anim->sprite_paths[4] = ft_strdup("sprites/anim/anim_5.png");
    game->anim->sprite_paths[5] = ft_strdup("sprites/gun.png");
    i = 0;
    while(i < 6)
    {
        if (!game->anim->sprite_paths[i])
        {
            exit_error("\033[31mError:\nFailed to allocate memory for sprite path\033[0m\n");
            while(i >= 0)
                free(game->anim->sprite_paths[i--]);
            exit_error("");
        }
        i++;
    }
}
void load_player_sprite(t_game *game)
{
    int             i;
    int             j;
    mlx_texture_t   *texture;

    init_and_set(game);
    i = 0;
    j = 0;
    while(i < 5)
    {
        texture = mlx_load_png(game->anim->sprite_paths[i]);
        if (!texture)
        {
            printf("\033[31mError:\nFailed to load\
 sprite: %s\033[0m\n", game->anim->sprite_paths[i]);
            while(j < i)
            {
                mlx_delete_texture(game->anim->player_texture[j]);
                j++;
            }
            exit_error("");
        }
        game->anim->player_texture[i] = texture;
        i++;
    }
}

void delete_current_sprite(t_game *game)
{
    int current_frame;

    current_frame = game->anim->current_frame;
    if (game->anim->player_sprites[current_frame])
    {
        mlx_delete_image(game->mlx, game->anim->player_sprites[current_frame]);
        game->anim->player_sprites[current_frame] = NULL;
    }
}

int load_next_sprite(t_game *game, int next_frame)
{
    int j;

    if (!game->anim->player_texture[next_frame])
    {
        j = 0;
        while (j < next_frame)
        {
            mlx_delete_texture(game->anim->player_texture[j]);
            j++;
        }
        printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", game->anim->sprite_paths[next_frame]);
        exit_error("");
        return (0);
    }
    return (1);
}

void display_next_sprite(t_game *game, int next_frame)
{
    game->anim->player_sprites[next_frame] = mlx_texture_to_image(game->mlx, game->anim->player_texture[next_frame]);
    if (!game->anim->player_sprites[next_frame])
    {
        printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m\n", next_frame);
        exit_error("");
    }
    mlx_image_to_window(game->mlx, game->anim->player_sprites[next_frame], 10, 0);
    game->anim->current_frame = next_frame;
}

void update_animation(void *param)
{
    t_game *game;
    double current_time;
    int next_frame;
    
    game = (t_game *)param;
    if (!game->anim->is_animating)
        return;
    current_time = mlx_get_time();
    if (current_time - game->anim->last_frame_time < 0.05)
        return;
    game->anim->last_frame_time = current_time;
    next_frame = game->anim->current_frame + 1;
    delete_current_sprite(game);
    if (next_frame < 5)
    {
        if (load_next_sprite(game, next_frame))
            display_next_sprite(game, next_frame);
    }
    else
        game->anim->is_animating = false;
}

void test_cursor(void *param)
{
    t_game	*info;

	info = (t_game *)param;
    if(mlx_is_mouse_down(info->mlx, MLX_MOUSE_BUTTON_LEFT) && !info->anim->is_animating)
    {
        info->anim->is_animating = true;
        info->anim->current_frame = 0;
        info->anim->last_frame_time = mlx_get_time(); 
    }
}