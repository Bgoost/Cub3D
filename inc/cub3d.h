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
# include <float.h>

# define WIDTH 1600
# define HEIGHT 1000
# define VALID_MAP_CHARS "10NSEW \n\t"

# define FOV 60
# define TILE 64

# define MAX_MAP_SIZE 1024
# define BUFF 4096
# define MAX_LINE_LEN 1024

# define CEILING_COLOR 0xA3E9DAff
# define WALL_COLOR 0xB76841ff
# define FLOOR_COLOR 0x869292ff

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_ray
{
	int		wall_height;
	int		first_wall_pixel;
	int		last_wall_pixel;
	double	projection_height; // amount of wall pixels
	double	distance_to_wall; 
	t_point	hit_point;
	double	angle;
}	t_ray;

typedef struct	s_raycasting
{
	double		ray_increment; // = FOV/WIDTH
	double		distance_to_plane; // = (WIDTH/2)/tan(FOV/2)
	double		direction; // N(90), S(270), W(180), E(0)
	t_point		player;
	mlx_t		*mlx;
	mlx_image_t	*image;
}	t_raycasting;

typedef struct  s_textures
{
    char *north;
    char *south;
    char *west;
    char *east;
    int floor_color[3];
    int ceiling_color[3];
}               t_textures;

typedef struct  s_map
{
    char **lines;
    char **map;
    int start;
    int end;
    int width;
    int height;
    int valid_map;
    int player_x;
    int player_y;
    char player_c;
    t_textures textures;
}               t_map;

// PARSING
int		main_checker(int argc, char *argv[], t_map **map);
int		cub_control(char *argv);
void	parse_scene_file(const char *filename, t_map *scene);
int		is_strspace(char *str);
char	*trim_whitespace(char *str);
int		is_valid_map_char(char c);
void	set_file_lines(const char *filename, t_map *scene, int lines_count);
int		get_lines_count(const char *filename);
void	parse_main_textures(char *line, t_map *scene);
void	parse_map(t_map *scene);

// RAYCASTING
double	degree_to_radian(double degree);
t_point	*horizontal_hit(t_point player, char **map, double angle);
t_point	*vertical_hit(t_point player, char **map, double angle);
double	point_distance(t_point hit, t_point player, char point);
void	cast_ray(t_raycasting info, char **map, t_ray *ray);
void	print_column(t_ray *ray, mlx_image_t *image, int x);
double	adjust_angle(double angle);
void	print_scene(t_raycasting info, char **map, t_ray *ray);

// UTILS
void	free_map(char **map);
void	free_scene(t_map **scene);
void	free_array(char **array);
void	exit_error(char *msg);

#endif
