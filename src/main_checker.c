/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:20:06 by martalop          #+#    #+#             */
/*   Updated: 2025/01/22 23:20:12 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_map *init_map()
{
    t_map *map;
    map = malloc(sizeof(t_map));
    if (map == NULL)
        exit_error("Error:\nMemory allocation failed for map.");
    map->lines = NULL;
    map->map = NULL;
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
    map->valid_map = 0;
    map->start = 0;
    map->end = 0;
    map->width = 0;
    map->height = 0;
    map->player_x = 0;
    map->player_y = 0;
    map->player_c = '\0';
    return map;
}

int main_checker(int argc, char *argv[], t_map **map)
{
    int fd;

    *map = init_map();
    if (argc != 2)
        exit_error("Usage: ./Cub3D t_map_name.cub");
    if (cub_control(argv[1]) == -1)
        return (exit_error("Invalid file extension:\nUsage: ./so_long name_map.ber"), 0);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (exit_error(strerror(errno)), 0);

    parse_scene_file(argv[1], *map);

    // Print map details
    printf("\n\nMap details:\n");
    printf("North texture: %s\n", (*map)->textures.north);
    printf("South texture: %s\n", (*map)->textures.south);
    printf("West texture: %s\n", (*map)->textures.west);
    printf("East texture: %s\n", (*map)->textures.east);
    printf("Floor color: %d, %d, %d\n", (*map)->textures.floor_color[0],
           (*map)->textures.floor_color[1], (*map)->textures.floor_color[2]);
    printf("Ceiling color: %d, %d, %d\n", (*map)->textures.ceiling_color[0],
           (*map)->textures.ceiling_color[1], (*map)->textures.ceiling_color[2]);
    printf("Map:\n");
    for (int i = 0; i < ((*map)->end - (*map)->start) + 1; i++)
        printf("%s\n", (*map)->map[i]);
    printf("Parsing successful!\n");

    return 1;
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
