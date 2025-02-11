#include "../inc/cub3d.h"

void errors_map_chars(t_map *scene, int i, int j)
{
    char *trimmed;

    if(is_strspace(scene->lines[i]))
    {
        printf("\033[31mError:\nEmpty lines not allowed in map.\033[0m");
        exit_error("");
    }
    if(!is_notvalid(scene->lines[i]))
    {
        trimmed = ft_strtrim(scene->lines[i], "\n");
        printf("\033[31mError:\nInvalid line [%s\033[0m", trimmed);
        free(trimmed);
        exit_error("] in map.");
    }
    if (!ft_strchr(VALID_MAP_CHARS, scene->lines[i][j]))
    {
        printf("\033[31mError:\nInvalid character [%c\033[0m", scene->lines[i][j]);
        exit_error("] in map.");
    }
}

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
    errors_map_chars(scene, i, j);
}

char *pad_line_to_width(const char *line, int width)
{
    char *padded = malloc(width + 1);
    int i = 0;

    if (!padded)
        exit_error("Error:\nMemory allocation for padded line failed.");

    while (line[i] && i < width)
    {
        padded[i] = line[i];
        i++;
    }
    while (i < width)
    {
        padded[i] = ' ';
        i++;
    }
    padded[width] = '\0';
    return padded;
}

void process_line(t_map *scene, int i, int *num_players, char **copy_map)
{
    int j;
    char *trimmed;
    char *padded_line;

    j = 0;
    trimmed = ft_strtrim(scene->lines[i], "\n");
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

void parse_map_errors(int num_players)
{
    if (num_players == 0)
        exit_error("Error:\nNo player position found.");
    if (num_players > 1)
        exit_error("Error:\nMultiple player positions found.");
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

char **init_allocate_map(int height, int width)
{
    char **map;
    int i;

    map = malloc(sizeof(char *) * (height + 1));
    if (!map)
        exit_error("Error:\nMemory allocation for map failed.");

    for (i = 0; i < height; i++)
    {
        map[i] = malloc(sizeof(char) * (width + 1));
        if (!map[i])
        {
            while (i > 0)
                free(map[--i]);
            free(map);
            exit_error("Error:\nMemory allocation for map row failed.");
        }
        ft_bzero(map[i], width);
        map[i][width] = '\0';
    }
    map[height] = NULL;
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
