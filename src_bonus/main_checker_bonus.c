/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 main_checker.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: martalop <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/01/22 23:20:06 by martalop		   #+#	  #+#			  */
/*	 Updated: 2025/02/26 16:44:10 by martalop		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../inc/cub3d_bonus.h"

static void	init_map_textures(t_map *map)
{
	map->textures.north = NULL;
	map->textures.south = NULL;
	map->textures.west = NULL;
	map->textures.east = NULL;
	map->textures.floor_color[0] = -1;
	map->textures.floor_color[1] = -1;
	map->textures.floor_color[2] = -1;
	map->textures.ceiling_color[0] = -1;
	map->textures.ceiling_color[1] = -1;
	map->textures.ceiling_color[2] = -1;
}

t_map	*init_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	printf("malloc map: %p\n", map);
	if (map == NULL)
		exit_error("Error:\nMemory allocation failed for map.");
	map->lines = NULL;
	map->map = NULL;
	init_map_textures(map);
	map->valid_map = -1;
	map->start = 0;
	map->end = 0;
	map->width = 0;
	map->height = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_c = '\0';
	return (map);
}

int	main_checker(int argc, char *argv[], t_map **map)
{
	int	fd;

	*map = init_map();
	if (argc != 2)
	{
		free_scene(map);
		exit_error("Error\nUsage: ./cub3D map.cub");
	}
	if (cub_control(argv[1]) == -1)
	{
		free_scene(map);
		return (exit_error("Error:\nInvalid file extension:\n\
Usage: ./cub3D map.cub"), 0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		free_scene(map);
		return (exit_error(strerror(errno)), 0);
	}
	parse_scene_file(argv[1], *map);
	return (1);
}

int	cub_control(char *argv)
{
	int		len;
	char	*word;
	int		i;

	word = ".cub";
	i = 0;
	len = ft_strlen(argv) - 4;
	if (len <= 0)
		return (-1);
	while (argv[len])
	{
		if (word[i] != argv[len])
			return (-1);
		i++;
		len++;
	}
	return (1);
}
