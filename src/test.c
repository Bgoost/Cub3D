/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:56:18 by martalop          #+#    #+#             */
/*   Updated: 2025/03/02 20:53:31 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

double	degree_to_radian(double degree)
{
	double	radian;
	
	radian = (degree * M_PI) / (double)180.0;
	return (radian);
}

t_point	*first_h_hit(double angle, t_point player)
{
	t_point	grid_player;
	t_point	*hit;

	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE; // + TILE / 2;
	grid_player.y = player.y * TILE; // + TILE / 2;
	if (angle <= 180 && angle >= 0)
		hit->y = floor(grid_player.y / TILE) * TILE - 0.0000000001; 
	else
		hit->y = floor(grid_player.y / TILE) * TILE + TILE; 
	hit->x = grid_player.x + (grid_player.y - hit->y) / tan(degree_to_radian(angle));
	return (hit);
}

void	horizontal_increments(double angle, t_point *increment)
{
	if (angle >= 0 && angle <= 180) 
		increment->y = -TILE;
	else
		increment->y = TILE;
	if (angle >= 90 && angle <= 270) 
		increment->x = -fabs(TILE / tan(degree_to_radian(angle)));
	else
		increment->x = fabs(TILE / tan(degree_to_radian(angle)));
}

int	safe_hit_point(double x, double y, int width, int height, char id)
{
	(void)id;
	if ((int)x / TILE < 0 || ((int)x / TILE) >= width)
		return (0);
	if ((int)y / TILE < 0 || ((int)y / TILE) >= height)
		return (0);
	return (1);
}

int	is_wall(double x, double y, t_game *info)
{
	int	x_;
	int	y_;

//	 printf("want to move to: x = %f y = %f\n", x, y);
	x_ = floor(x);
	y_ = floor(y);
 //	printf("checking wall at: x = %d y = %d\n\n", x_, y_);
	if (info->map[y_][x_] == '1')
	{
//		printf("wall found at x = %f y = %f (%d, %d)\n", x, y, x_, y_);
		return (1);
	}
//	printf("NO wall found at x = %f y = %f\n", x, y);
	return (0);
}


int	safe_map_point(double x, double y, int width, int height)
{
	// recibimos coordenadas en unidades de 1 x 1 pero con decimales (ej; (2'25, 5))
	if (x < 0 || ceil(x) >= width)
		return (0);
	if (y < 0 || ceil(y) >= height)
		return (0);
	return (1);
}

t_point	*horizontal_hit(t_point player, char **map, double angle, t_game *info)
{
	t_point	*hit;
	t_point	increment;

//	printf("HORIZONTAL HITS\n");	
	hit = first_h_hit(angle, player);
	if (!hit)
		return (NULL);
	if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height, 'h'))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1') // we find WALL, we stop
		return (hit);
	horizontal_increments(angle, &increment);
	while (map[(int)hit->y / TILE][(int)hit->x / TILE] == '0') 
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
		if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height, 'h'))
			return (hit);
	}
	return (hit);
}

t_point	*first_v_hit(double angle, t_point player)
{
	t_point	*hit;
	t_point	grid_player;
	
	hit = malloc(sizeof(t_point) * 1);
	if (!hit)
		return (NULL);
	grid_player.x = player.x * TILE; //+ TILE / 2;
	grid_player.y = player.y * TILE; //+ TILE / 2;

	if (angle <= 270 && angle >= 90) 
		hit->x = floor(grid_player.x / TILE) * TILE - 0.0000000001; 
	else
		hit->x = floor(grid_player.x / TILE) * TILE + TILE;
	hit->y = grid_player.y + (grid_player.x - hit->x) * tan(degree_to_radian(angle));
	return (hit);
}

void	vertical_increment(double angle, t_point *increment)
{
	if (angle <= 270 && angle >= 90)
		increment->x = -TILE;
	else
		increment->x = TILE;

	if (angle <= 180 && angle >= 0) 
		increment->y = -fabs(TILE * tan(degree_to_radian(angle)));
	else
		increment->y = fabs(TILE * tan(degree_to_radian(angle)));
}

t_point	*vertical_hit(t_point player, char **map, double angle, t_game *info)
{
	t_point	*hit;
	t_point	increment;

//	printf("VERTICAL HITS\n");	
	hit = first_v_hit(angle, player);	
	if (!hit)
		return (NULL);
	if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height, 'v'))
		return (hit);
	if (map[(int)hit->y / TILE][(int)hit->x / TILE] == '1')
		return (hit);
	vertical_increment(angle, &increment);
	while (map[((int)hit->y / TILE)][(int)hit->x / TILE] == '0')
	{
		hit->x = hit->x + increment.x;
		hit->y = hit->y + increment.y;
		if (!safe_hit_point(hit->x, hit->y, info->map_width, info->map_height, 'v'))
			return (hit);
	}
	return (hit);
}

double	point_distance(t_point hit, t_point player, char point)
{
	(void)point;
	double	distance;
	t_point	grid_player;
	
	grid_player.x = (player.x * TILE); // + (TILE / 2);
	grid_player.y = (player.y * TILE); // + (TILE / 2);

	distance = sqrt(pow((grid_player.x - hit.x), 2) + pow((grid_player.y - hit.y), 2));
	return (distance);
}

void	set_distance(double distance, t_ray *ray, t_point *hit_point, char id)
{
	ray->distance_to_wall = distance;
	ray->hit_point = hit_point;
	ray->wall_hit = id;
}

void	find_distance(t_point *v_hit, t_point *h_hit, t_ray *ray, t_game *info)
{
	//float	double_max;
	double	v_distance;
	double	h_distance;
	
//	double_max = 1.8 * pow(10, 308);
//	printf("DISTANCE\n");	
//	if (v_hit->y < 0 || ((int)v_hit->y / TILE) > info->map_height || v_hit->x < 0 || ((int)v_hit->x / TILE) > info->map_width)
//	if (!safe_hit_point(v_hit->x, v_hit->y, info->map_width, info->map_height, 'v'))
//		v_distance = double_max;
//	else
		v_distance = point_distance(*v_hit, info->player, 'v');
//	if (h_hit->y < 0 || ((int)h_hit->y / TILE) > info->map_height || h_hit->x < 0 || ((int)h_hit->x / TILE) > info->map_width)
//	if (!safe_hit_point(h_hit->x, h_hit->y, info->map_width, info->map_height, 'h'))
//		h_distance = double_max;
//	else
		h_distance = point_distance(*h_hit, info->player, 'h');
	if (v_distance < h_distance)
	{
		set_distance(v_distance, ray, v_hit, 'v');
		free(h_hit);
	}
	else
	{
		set_distance(h_distance, ray, h_hit, 'h');
		free(v_hit);
	}
	ray->distance_to_wall = ray->distance_to_wall * cos(degree_to_radian(ray->angle - info->direction));
}

int	cast_ray(t_game *info, char **map, t_ray *ray)
{
	t_point	*v_hit;
	t_point	*h_hit;
	t_point	center;

	center.x = WIN_WIDTH / 2;
	center.y = WIN_HEIGHT / 2;

//	printf("\n\nANGLE %f\n-------------------------\n", ray->angle);
//	printf("map player in double: (%f, %f)\n", info->player.x, info->player.y);
	h_hit = horizontal_hit(info->player, map, ray->angle, info);
	if (!h_hit) 
		return (0); // malloc error
	v_hit = vertical_hit(info->player, map, ray->angle, info);
	if (!v_hit)
		return (free(h_hit), 0); // malloc error
	find_distance(v_hit, h_hit, ray, info);
	ray->projection_height = (TILE / ray->distance_to_wall) * info->distance_to_plane;
//	printf("\nprojection height: %f\n", ray->projection_height);

//	printf("test.1: %f\n", ray->projection_height / info->distance_to_plane);
//	printf("test.2: %f\n", TILE / ray->distance_to_wall);
	if ((ray->projection_height / info->distance_to_plane) - (TILE / ray->distance_to_wall) > 0.0001)
	{
	 	ft_putstr_fd("ERROR with projection heigth!\n", 2);
		exit (1);
	}
	ray->projection_height = ceil(ray->projection_height); 
	ray->first_wall_pixel = center.y - (ray->projection_height / 2);
	ray->last_wall_pixel = ray->first_wall_pixel + ray->projection_height;

	if (ray->projection_height > WIN_HEIGHT - 1 || ray->projection_height < 0)
		adjust_pixels(&ray->first_wall_pixel, &ray->last_wall_pixel);
//	printf("FIRST pixels modified: %d\n", ray->first_wall_pixel);
//	printf("LAST pixels modified: %d\n", ray->last_wall_pixel);
	return (1);
}

void	handle_y_texture(t_math_texture *t, mlx_texture_t *wall_texture)
{
	t->texture_in.y = (int)t->text_pos % wall_texture->height;
	if (t->texture_in.y < 0)
		t->texture_in.y += wall_texture->height;
	t->text_pos += t->step;
}

void	print_wall(int x, int *y, t_game *info, t_math_texture *t)
{
	uint32_t		texture_color;

	if (info->ray->last_wall_pixel == WIN_HEIGHT - 1)
		info->ray->last_wall_pixel += 1;
	while (*y < info->ray->last_wall_pixel) 
	{
		handle_y_texture(t, info->ray->wall_texture);
		texture_color = get_texture_pixel(info->ray->wall_texture, t->texture_in.x, t->texture_in.y);
		mlx_put_pixel(info->image, x, *y, texture_color);
		if (*y + 1 == info->ray->last_wall_pixel && *y + 1 != WIN_HEIGHT - 1)
			return ;
		*y += 1;
	}
}

void	handle_xy_texture(t_math_texture *t, t_ray *ray)
{
	t->step = (double)ray->wall_texture->height / ray->projection_height;
	t->text_pos = (ray->first_wall_pixel - WIN_HEIGHT / 2 + ceil(ray->projection_height / 2)) * t->step;
	if (ray->wall_hit == 'v')
		t->texture_in.x = fmod(ray->hit_point->y, TILE);
	else 
		t->texture_in.x = fmod(ray->hit_point->x, TILE);
	t->texture_in.x = (t->texture_in.x / TILE) * ray->wall_texture->width;
}

void	print_column(t_ray *ray, t_game *info, int x)
{
	int				y;
	t_math_texture	text_info;
	
	y = 0;
	ray->wall_texture = get_wall_texture(ray, info->textures);
	if (!ray->wall_texture)
	{
		ft_putstr_fd("something weird happened with textures\n", 2);
		exit(1);
	}
	handle_xy_texture(&text_info, ray);
	while (y < WIN_HEIGHT)
	{
		if (y < ray->first_wall_pixel)
			mlx_put_pixel(info->image, x, y, info->ceiling_color);
		else if (y >= ray->first_wall_pixel && y < ray->last_wall_pixel)
			print_wall(x, &y, info, &text_info);
		else if (y < WIN_HEIGHT)
			mlx_put_pixel(info->image, x, y, info->floor_color);
		y++;
	}
}

double	adjust_angle(double angle)
{
	double res;

	res = 0;
	res = fmod(angle, 360.0);
	if (res <= 0.0)
		res = res + 360.0;
   	return (res);
}

void	print_scene(t_game *info, char **map, t_ray *ray)
{
	int		x;
	
	x = 0;
//	printf("player (%f, %f)\n", info->player.x, info->player.y);
	ray->angle = info->direction + (FOV / 2);
	while (x < WIN_WIDTH)
	{
		ray->angle = adjust_angle(ray->angle);
		if (!cast_ray(info, map, ray)) // malloc error
			exit (1);
		print_column(ray, info, x);
		free(ray->hit_point);
		ray->angle = ray->angle - info->ray_increment;
		x++;
	}
	// con este push image to window va peor y MÁS LENTO!
	//if (mlx_image_to_window(info->mlx, info->image, 0, 0) == -1)
	//	{
	//		mlx_close_window(info->mlx);
	//		//free
	//		exit(1);
	//	}

	// BONUS
    draw_minimap(info->image, info->map, info);
	
	mlx_image_to_window(info->mlx, mlx_texture_to_image(info->mlx, mlx_load_png("sprites/gun.png")), 0, 0);
//	 draw_player(info);

	// animation_loop(info);
	//every 100 frame draw playe
	// draw_player(info);
}

void	handle_ws_movements(t_game *info, mlx_t *mlx, t_point tmp)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		tmp.y -= 0.1001 * sin(degree_to_radian(info->direction));
		// restamos porque cuando los rayos miran abajo, sin es negativo y como queremos avanzar, la y será positiva
		tmp.x += 0.1001 * cos(degree_to_radian(info->direction));
		// tenemos que sumar en player.x porque el resultado de cos puede ser negativo(cuando rayo mira a la izquierda) o positivo
		/*if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}*/
		// BONUS - COLISIONES
		if (safe_map_point(tmp.x, info->player.y, info->map_width, info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width, info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		tmp.y += 0.1001 * sin(degree_to_radian(info->direction));
		tmp.x -= 0.1001 * cos(degree_to_radian(info->direction));
		/*if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}*/
		// BONUS - COLISIONES
		if (safe_map_point(tmp.x, info->player.y, info->map_width, info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width, info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
}

void	handle_ad_movements(t_game *info, mlx_t *mlx, t_point tmp)
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		tmp.x -= 0.1001 * sin(degree_to_radian(info->direction));
		tmp.y -= 0.1001 * cos(degree_to_radian(info->direction));
		/*if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}*/
		// BONUS - COLISIONES
		if (safe_map_point(tmp.x, info->player.y, info->map_width, info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width, info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		tmp.x += 0.1001 * sin(degree_to_radian(info->direction));
		tmp.y += 0.1001 * cos(degree_to_radian(info->direction));
		/*if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			print_scene(info, info->map, info->ray);
		}*/
		// BONUS - COLISIONES
		if (safe_map_point(tmp.x, info->player.y, info->map_width, info->map_height) && !is_wall(tmp.x, info->player.y, info))
			info->player.x = tmp.x;
		if (safe_map_point(info->player.x, tmp.y, info->map_width, info->map_height) && !is_wall(info->player.x, tmp.y, info))
			info->player.y = tmp.y;
		print_scene(info, info->map, info->ray);
	}
}




/*void	key_input(mlx_key_data_t keydata, void *param)
{
	(void)keydata;
	t_game	*info;
	t_point	tmp;
	
	info = (t_game *)param;
	tmp = info->player;
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->direction += 5;
		info->redisplay = 1;
	}	
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 5;
		info->redisplay = 1;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		tmp.x -= 0.20 * sin(degree_to_radian(info->direction));
		tmp.y -= 0.20 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			info->redisplay = 1;
		}
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		tmp.x += 0.20 * sin(degree_to_radian(info->direction));
		tmp.y += 0.20 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			info->redisplay = 1;
		}
	}
	if ( mlx_is_key_down(info->mlx, MLX_KEY_W))
	{
		tmp.y -= 0.20 * sin(degree_to_radian(info->direction));
		tmp.x += 0.20 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			info->redisplay = 1;
		}
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S))
	{
		tmp.y += 0.20 * sin(degree_to_radian(info->direction));
		tmp.x -= 0.20 * cos(degree_to_radian(info->direction));
		if (safe_map_point(tmp.x, tmp.y, info->map_width, info->map_height))
		{
			info->player.x = tmp.x;
			info->player.y = tmp.y;
			info->redisplay = 1;
		}
	}
}*/

void	player_movements(void *param)
{
//	(void)keydata;
	t_game	*info;
	t_point			tmp;

	info = (t_game *)param;
	tmp.x = info->player.x;
	tmp.y = info->player.y;
	test_cursor(info);
	update_animation(param);
	//printf("someone pressed a key\n");
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
	{
		mlx_delete_image(info->mlx, info->image);
		mlx_close_window(info->mlx);
		exit(0);
	}
/*	if (info->redisplay)
	{
		print_scene(info, info->map, info->ray);
		info->redisplay = 0;
	}*/
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->direction += 2.5;
		print_scene(info, info->map, info->ray);
	}	
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->direction -= 2.5;
		print_scene(info, info->map, info->ray);
	}
	handle_ws_movements(info, info->mlx, tmp);
	handle_ad_movements(info, info->mlx, tmp);
}
void free_sprites(t_game *game)
{
    int i = 0;

    while (i < 5)
    {
        if (game->anim.player_sprites[i])
        {
            mlx_delete_image(game->mlx, game->anim.player_sprites[i]);
            game->anim.player_sprites[i] = NULL;
        }
        i++;
    }
}


void	free_game(t_game *game)
{
	free_sprites(game);
	mlx_delete_image(game->mlx, game->image);
    mlx_terminate(game->mlx);
	free_mlx_textures(game->textures);
	free(game->ray);
	free(game);
}
