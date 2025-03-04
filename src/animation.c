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
    {
        anim->player_sprites[i] = NULL;
        i++;
    }
    i = 0;
    while(i < 6)
    {
        anim->sprite_paths[i] = NULL;
        i++;
    }
    i = 0;
    while(i < 6)
    {
        anim->player_texture[i] = NULL;
        i++;
    }
    return (anim);
}
void init_and_set(t_game *game)
{
    int             i;

    // game->anim = init_anim();
    // if (!game->anim)
    // {
    //     printf("\033[31mError:\nFailed to initialize animation\033[0m\n");
    //     exit_error("");
    // }
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
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", game->anim->sprite_paths[i]);
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

// void	set_anim_values(char **sprite_paths, t_anim *anim)
// {
// 	anim->current_frame = 0;
// 	anim->frame_counter = 0;
// 	anim->frame_speed = 100;
// 	anim->sprites = NULL;
// 	sprite_paths[0] = "sprites/anim/anim_1.png";
// 	sprite_paths[1] = "sprites/anim/anim_2.png";
// 	sprite_paths[2] = "sprites/anim/anim_3.png";
// 	sprite_paths[3] = "sprites/anim/anim_4.png";
// 	sprite_paths[4] = "sprites/anim/anim_5.png";
// 	sprite_paths[5] = "sprites/anim/anim_6.png";
// 	sprite_paths[6] = "sprites/anim/anim_7.png";
// 	sprite_paths[7] = "sprites/anim/anim_8.png";
// 	sprite_paths[8] = NULL;
// }

// void	load_player_sprite(t_game *game)
// {
// 	int				i;
// 	char			*sprite_paths[9];
// 	mlx_texture_t	*texture;

// 	set_anim_values(sprite_paths, &game->anim);
// 	i = 0;
// 	while (i < 8)
// 	{
// 		texture = mlx_load_png(sprite_paths[i]);
// 		if (!texture)
// 		{
// 			printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", sprite_paths[i]);
// 			exit_error("");
// 		}
// 		game->anim.player_texture[i] = texture;
// 		game->anim.player_sprites[i] = mlx_texture_to_image(game->mlx, texture);
// 		if (!game->anim.player_sprites[i])
// 		{
// 			printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m\n", i);
// 			exit_error("");
// 		}
// 		//mlx_delete_texture(texture);
// 		i++;
// 	}
// }

// void	draw_player_gun(t_game *game)
// {
// 	int			i;
// //	mlx_image_t	*new_sprite;
// 	mlx_texture_t	*texture;
// 	mlx_image_t	*frame;
	

// 	i = game->anim.current_frame;
// //	new_sprite = game->anim.player_sprites[i];

// 	texture = game->anim.player_texture[i];
// 	frame = mlx_texture_to_image(game->mlx, texture);
// 	if (!frame)
// 	{
// 		printf("\033[31mError: Player sprite at frame %d is NULL\033[0m\n", i);
// 		return ;
// 	}
// 	game->anim.player_sprites[i] = frame;

// 	mlx_image_to_window(game->mlx, frame, 0, 0);
// 	if (i != 0)
// 		mlx_delete_image(game->mlx, game->anim.player_sprites[i - 1]);
// 	else
// 		mlx_delete_image(game->mlx, game->anim.player_sprites[7]);
// 	game->anim.current_frame = (i + 1) % 8;
// }

void update_animation(void *param)
{
    t_game *game = (t_game *)param;
    if (!game->anim->is_animating)
        return;

    double current_time = mlx_get_time();
    if (current_time - game->anim->last_frame_time < 0.05)
        return;

    game->anim->last_frame_time = current_time;
    int current_frame = game->anim->current_frame;
    int next_frame = current_frame + 1;

    // Delete current image
    if (game->anim->player_sprites[current_frame])
    {
        mlx_delete_image(game->mlx, game->anim->player_sprites[current_frame]);
        game->anim->player_sprites[current_frame] = NULL;
    }

    if (next_frame < 5)
    {
        // Load and convert next frame
        if (!game->anim->player_texture[next_frame])
        {
            for (int j = 0; j < next_frame; j++)  // Free already loaded textures
            {
                mlx_delete_texture(game->anim->player_texture[j]);
            }
            printf("\033[31mError:\nFailed to load sprite: %s\033[0m\n", game->anim->sprite_paths[next_frame]);
            exit_error("");
        }

        game->anim->player_sprites[next_frame] = mlx_texture_to_image(game->mlx, game->anim->player_texture[next_frame]);
        if (!game->anim->player_sprites[next_frame])
        {
            printf("\033[31mError:\nFailed to convert texture to image for sprite %d\033[0m\n", next_frame);
            exit_error("");
        }
        mlx_image_to_window(game->mlx, game->anim->player_sprites[next_frame], 10, 0);
        game->anim->current_frame = next_frame;
    }
    else
    {
        game->anim->is_animating = false;
    }
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