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

# define WIDTH 1600
# define HEIGHT 1000

# define FOV 60
# define TILE 64

# define MAX_MAP_SIZE 1024
# define BUFF 4096
# define MAX_LINE_LEN 1024

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_ray
{
	int		wall_height;
	int		projection_height; // amount of wall pixels
	int		distance_to_wall; 
	int		x_increment;
	int		y_increment;
}	t_ray;

typedef struct	s_raycasting
{
	double	ray_increment; // = FOV/WIDTH
	int		distance_to_plane; // = (WIDTH/2)/tan(FOV/2)
	int		angle; // cambia segun N(90), S(270), W(180), E(360)
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
    int player_x;
    int player_y;
    char player_c;
    t_textures textures;
}               t_map;

void	exit_error(char *msg);
int		main_checker(int argc, char *argv[], t_map **map);
int		cub_control(char *argv);
void	parse_scene_file(const char *filename, t_map *scene);
void	free_scene(t_map **scene);
int		is_strspace(char *str);
char	*trim_whitespace(char *str);
int		is_valid_map_char(char c);
void	set_file_lines(const char *filename, t_map *scene, int lines_count);
int		get_lines_count(const char *filename);
void	parse_main_textures(char *line, t_map *scene);
void free_map(char **map);


#endif
