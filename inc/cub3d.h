/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:58:57 by martalop          #+#    #+#             */
/*   Updated: 2025/02/19 16:40:51 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include "colors.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>

# define WIN_WIDTH 1600
# define WIN_HEIGHT 1000
# define VALID_MAP_CHARS "10NSEW \n\t"

# define FOV 60
# define TILE 64

# define MAX_MAP_SIZE 1024
# define BUFF 4096
# define MAX_LINE_LEN 1024

# define CEILING_COLOR 0xA3E9DAff
# define WALL_COLOR 0xB76841ff
# define FLOOR_COLOR 0x869292ff

typedef struct s_sprite
{
	mlx_image_t	*sprite;
	struct s_sprite *next;
}	t_sprite;

typedef struct s_anim
{
	// mlx_image_t	*player_sprites[9];
	mlx_texture_t	*frame1;
	mlx_texture_t	*frame2;
	mlx_texture_t	*frame3;
	mlx_texture_t	*frame4;
	mlx_texture_t	*frame5;
	mlx_texture_t	*frame6;
	mlx_texture_t	*frame7;
	mlx_texture_t	*frame8;
	mlx_texture_t	*frame9;
	mlx_texture_t	*frame10;
	mlx_image_t		*curren_img;
	mlx_image_t		*player_sprites[9];
	mlx_instance_t		*player_instance;
	int frame_speed;
	double 	accum;
	t_sprite *sprites;
	int		 index;
	int		 time;
	int         current_frame;
	int         frame_counter;
}	t_anim;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_textures;

typedef struct s_ray
{
	int				first_wall_pixel;
	int				last_wall_pixel;
	double			projection_height; // amount of wall pixels
	double			distance_to_wall;
	double			angle;
	t_point			*hit_point;
	char			wall_hit;
	mlx_texture_t	*wall_texture;
}	t_ray;

typedef struct s_game
{
	double			ray_increment;
	double			distance_to_plane;
	double			direction; // N(90), S(270), W(180), E(0)
	t_point			player;
	mlx_t			*mlx;
	mlx_image_t		*image;
	char			**map;
	t_ray			*ray;
	int				map_width;
	int				map_height;
	t_textures		textures;
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	t_anim			anim;
}	t_game;

typedef struct s_map
{
	char		**lines;
	char		**map;
	int			start;
	int			end;
	int			width;
	int			height;
	int			valid_map;
	int			player_x;
	int			player_y;
	char		player_c;
	t_textures	textures;
}	t_map;

// PARSING
int		main_checker(int argc, char *argv[], t_map **map);
int		cub_control(char *argv);
void	parse_scene_file(const char *filename, t_map *scene);
int		is_strspace(char *str);
char	*trim_whitespace(char *str);
int		is_valid_map_char(char c);
void	set_file_lines(const char *filename, t_map *scene, int lines_count);
int		get_lines_count(const char *filename);
void	parse_main_textures(char *line, t_map *scene, int map_started);
void	parse_map(t_map *scene);
char **init_allocate_map(int height, int width);
void set_map_chars(t_map *scene, int i, int j, int *num_players);
void parse_map_errors(int num_players);
char *pad_line_to_width(const char *line, int width);
int	extract_texture_path(const char *trimmed, char *result);
void	error_invalid_identifier(char *trimmed);


// RAYCASTING
double			degree_to_radian(double degree);
t_point			*horizontal_hit(t_point player, char **map, double angle, \
																t_game *info);
t_point			*vertical_hit(t_point player, char **map, double angle, \
																t_game *info);
double			point_distance(t_point hit, t_point player, char point);
t_game			*init_raycasting(t_map map);
int				cast_ray(t_game *info, char **map, t_ray *ray);
void			print_column(t_ray *ray, t_game *info, int x);
double			adjust_angle(double angle);
void			print_scene(t_game *info, char **map, t_ray *ray);
void			adjust_pixels(int *first_wall_pixel, int *last_wall_pixel);
uint32_t		get_ceiling_color(int *ceiling_color);
uint32_t		get_floor_color(int *floor_color);
mlx_texture_t	*get_wall_texture(t_ray *ray, t_textures textures);
uint32_t		get_texture_pixel(mlx_texture_t *texture, int x, int y);


// KEYBOARD
void			player_movements(void *param);

//MINIMAP
void draw_minimap(mlx_image_t *image, char **map, t_game *info);
void animate_player(void *param);
void load_player_sprite(t_game *info);
void	animation_loop(void *param);
void animate(void *param);
void load_sprites(t_game *info);
void draw_player(t_game *info);
void	animation_loop2(t_game *game);
void	init_anim(t_game *game);
void update(void * ptr);



// UTILS
void			free_map(char **map);
void			free_scene(t_map **scene);
void			exit_error(char *msg);
void			free_game(t_game *game);
int				is_notvalid(char *str);
void			free_sprites(t_sprite **lst);


#endif
