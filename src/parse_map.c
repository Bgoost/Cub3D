#include "../inc/cub3d.h"


void process_line(t_map *scene, int i, int *num_players, char **copy_map)
{
    int j;
    
    j = 0;
    scene->map[i - scene->start] = strdup(ft_strtrim(scene->lines[i], "\n"));
    copy_map[i - scene->start] = strdup(scene->map[i - scene->start]);
    if (!scene->map[i - scene->start] || !copy_map[i - scene->start])
        exit_error("Error: Memory allocation for map line failed.");
    while (scene->lines[i][j] != '\0')
    {
        if (ft_strchr("NSEW", scene->lines[i][j]))
        {
            scene->player_x = j;
            scene->player_y = i - scene->start;
            scene->player_c = scene->lines[i][j];
            if (*num_players > 0)
                exit_error("Error: Multiple player positions found.");
            (*num_players)++;
        }
        if (!ft_strchr(VALID_MAP_CHARS, scene->lines[i][j]))
            exit_error("Error: Invalid character in map.");
        j++;
    }
}

void parse_map_errors(int num_players)
{
    if (num_players == 0)
        exit_error("Error: No player position found.");
    if (num_players > 1)
        exit_error("Error: Multiple player positions found.");
}

int is_valid_map(t_map *map, char **copy_map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while(x < map->width)
    {
        if (copy_map[0][x] == 'F' || copy_map[(map->end - map->start)][x] == 'F')
            return (0);
        x++;
    }
    while(y <= (map->end - map->start))
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
        exit_error("Error: spaces not admited inside of the map.\n");
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

char    **init_allocate_map(int height)
{
    char **map;
    int i;

    map = malloc(sizeof(char *) * (height + 1));
    i = 0;
    if (!map)
        exit_error("Error: Memory allocation for map failed.");
    while (i < height + 1)
    {
        (map)[i] = NULL;
        i++;
    }
    return (map);
}

void    validate_and_clean_map(t_map *scene, char **copy_map, int num_players)
{
    if (!is_valid_map(scene, copy_map))
    {
        free_map(copy_map);
        exit_error("Error: Map is not closed.");
    }
    flood_fill(copy_map, scene, scene->player_x, scene->player_y);
    parse_map_errors(num_players);
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
    scene->map = init_allocate_map(scene->height);
    copy_map = init_allocate_map(scene->height);
    while (i <= scene->end)
    {
        process_line(scene, i, &num_players, copy_map);
        i++;
    }
    flood_fill(copy_map, scene, scene->player_x, scene->player_y);
    validate_and_clean_map(scene, copy_map, num_players);
}
