#include "../inc/cub3d.h"

void process_line(t_map *scene, int i, int *num_players, char **copy_map)
{
    int j;
    char *trimmed;
    char *padded_line;

    j = 0;
    trimmed = ft_strtrim(scene->lines[i], " \n");
    if (!trimmed)
        exit_error("Error:\nMemory allocation for trimmed line failed.");
    padded_line = pad_line_to_width(trimmed, scene->width);
    if (!padded_line)
        exit_error("Error:\nMemory allocation for padded line failed.");
    if (scene->map[i - scene->start])
        free(scene->map[i - scene->start]);
    if (copy_map[i - scene->start])
        free(copy_map[i - scene->start]);
    scene->map[i - scene->start] = padded_line;
    copy_map[i - scene->start] = pad_line_to_width(trimmed, scene->width);
    free(trimmed);
    if (!scene->map[i - scene->start] || !copy_map[i - scene->start])
        exit_error("Error:\nMemory allocation for map line failed.");
    while (scene->lines[i][j] != '\0')
    {
        set_map_chars(scene, i, j, num_players);
        j++;
    }
}

int is_valid_map(t_map *map, char **copy_map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x < map->width) 
    {
        if (copy_map[0][x] == 'F' || copy_map[map->height - 1][x] == 'F')
            return (0);
        x++;
    }
    while(y < map->height )
    { 
        if (copy_map[y][0] == 'F' || copy_map[y][map->width - 1] == 'F')
            return (0);
        y++;
    }
    map->valid_map = 1;
    return (1);
}

static void	flood_fill(char **copy_map, t_map *map, int x, int y)
{
    if(map->valid_map && copy_map[y][x] == ' ')
        exit_error("Error:\nMap is not surrounded by walls.");
    if(!map->valid_map)
    {
        if (x < 0 || x >= map->width || y < 0 || y >= map->height
            || copy_map[y][x] == '1' || copy_map[y][x] == 'F' || copy_map[y][x] == ' ')
            return ;
        copy_map[y][x] = 'F';
    }
    else
    {
        if (x < 0 || x >= map->width || y < 0 || y >= map->height
            || copy_map[y][x] == '1' || copy_map[y][x] == 'X')
            return ;
        copy_map[y][x] = 'X';
    }
	flood_fill(copy_map, map, x + 1, y);
	flood_fill(copy_map, map, x - 1, y);
	flood_fill(copy_map, map, x, y + 1);
	flood_fill(copy_map, map, x, y - 1);
}


void    validate_and_clean_map(t_map *scene, char **copy_map, int num_players)
{
    int is_valid;

    is_valid = is_valid_map(scene, copy_map);

    parse_map_errors(num_players);
    if (!is_valid || is_valid == -1)
    {
        free_map(copy_map);
        exit_error("Error:\nMap is not surrounded by walls.");
    }
    flood_fill(copy_map, scene, scene->player_x, scene->player_y);
    free_map(copy_map);
}

void    parse_map(t_map *scene)
{
    char **copy_map;
    int num_players;
    int i;

    scene->height = scene->end - scene->start + 1;
    num_players = 0;
    i = scene->start;
    scene->map = init_allocate_map(scene->height, scene->width);
    if(!scene->map)
        exit_error("Error:\nMemory allocation for map failed.");
    copy_map = init_allocate_map(scene->height, scene->width);
    if(!copy_map)
    {
        free_map(scene->map);
        exit_error("Error:\nMemory allocation for map failed.");
    }
    while (i <= scene->end)
    {
        process_line(scene, i, &num_players, copy_map);
        i++;
    }
    flood_fill(copy_map, scene, scene->player_x, scene->player_y);
    validate_and_clean_map(scene, copy_map, num_players);
}
