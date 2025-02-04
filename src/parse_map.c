#include "../inc/cub3d.h"

void set_map_chars(t_map *scene, int i, int j, int *num_players)
{
    if (ft_strchr("NSEW", scene->lines[i][j]))
    {
        scene->player_x = j;
        scene->player_y = i - scene->start;
        scene->player_c = scene->lines[i][j];
        if (*num_players > 0)
            exit_error("Error:\nMultiple player positions found.");
        (*num_players)++;
    }
    if (!ft_strchr(VALID_MAP_CHARS, scene->lines[i][j]))
    {
        printf("\033[31mError:\nInvalid character [%c\033[0m", scene->lines[i][j]);
        exit_error("] in map.");
    }
}

void process_line(t_map *scene, int i, int *num_players, char **copy_map)
{
    int j;
    char *trimmed;
    
    j = 0;
    trimmed = ft_strtrim(scene->lines[i], "\n");
    if (!trimmed)
        exit_error("Error:\nMemory allocation for trimmed line failed.");
    scene->map[i - scene->start] = ft_strdup(trimmed);
    copy_map[i - scene->start] = ft_strdup(trimmed);
    free(trimmed);
    while (scene->lines[i][j] != '\0')
    {
        set_map_chars(scene, i, j, num_players);
        j++;
    }
}

void parse_map_errors(int num_players)
{
    if (num_players == 0)
        exit_error("Error:\nNo player position found.");
    if (num_players > 1)
        exit_error("Error:\nMultiple player positions found.");
}

int is_valid_map(t_map *map, char **copy_map)
{
    int xy[2];
    int len;
    char *trimmed;

    xy[0] = 0;
    xy[1] = 0;
    while(xy[0] < map->width)
    {
        if (copy_map[0][xy[0]] == 'F' || copy_map[map->height - 1][xy[0]] == 'F')
            return (0);
        xy[0]++;
    }
    while(xy[1] < map->height)
    {
        if (copy_map[xy[1]][0] == 'F' || copy_map[xy[1]][map->width - 1] == 'F')
            return (0);
        xy[1]++;
    }
    trimmed = ft_strtrim(map->lines[map->end], "\n");
    len = ft_strlen(trimmed);
    free(trimmed);
    if(map->lines[map->end][len - 1] != '1')
        return (-1);
    map->valid_map = 1;
    return (1);
}

static void	flood_fill(char **copy_map, t_map *map, int x, int y)
{
    if(map->valid_map && copy_map[y][x] == ' ')
        exit_error("Error:\nspaces not admited inside of the map.\n");
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
        exit_error("Error:\nMemory allocation for map failed.");
    while (i < height + 1)
    {
        (map)[i] = NULL;
        i++;
    }
    return (map);
}

void    validate_and_clean_map(t_map *scene, char **copy_map, int num_players)
{
    int is_valid;

    is_valid = is_valid_map(scene, copy_map);
    parse_map_errors(num_players);
    if (!is_valid || is_valid == -1)
    {
        free_map(copy_map);
        if(is_valid == -1)
            exit_error("Error:\nMap can't end in a enter.");
        else
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
