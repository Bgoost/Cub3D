#include "../inc/cub3d.h"
#define VALID_MAP_CHARS "10NSEW \n\t"

void find_delimiter(char *line, int i, t_map *scene)
{
    int width;
    if(!is_strspace(line))
    {
        width = ft_strlen(line);
        if(line[width - 1] == '\n')
            width--;
        if(width > scene->width)
            scene->width = width;
        if (scene->start == 0)
            scene->start = i;
        scene->end = i;
    }
}

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
        {
            printf("[%c]\n", scene->lines[i][j]);
            printf("line: %s\n", scene->lines[i]);
            exit_error("Error: Invalid character in map.");
        }
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
    return (1);
}

void free_map(char **map)
{
    int i;

    i = 0;
    if (!map)
        return;

    while(map[i] != NULL)
    {
        free(map[i]);
        map[i] = NULL;
        i++;
    }
    free(map);
}

static void	flood_fill(char **copy_map, t_map *map, int x, int y, int is_valid)
{
	if (x < 0 || x >= map->width || y < 0 || y >= (map->end - map->start) + 1
		|| copy_map[y][x] == '1' || copy_map[y][x] == 'F')
		return ;
    copy_map[y][x] = 'F';
    if(is_valid)
    {
        //dsjhkhas
    }
	flood_fill(copy_map, map, x + 1, y, is_valid);
	flood_fill(copy_map, map, x - 1, y, is_valid);
	flood_fill(copy_map, map, x, y + 1, is_valid);
	flood_fill(copy_map, map, x, y - 1, is_valid);
}

void parse_map(t_map *scene)
{
    int i;
    int num_players;
    char **copy_map;

    i = scene->start;
    scene->height = scene->end - scene->start + 1;
    num_players = 0;
    scene->map = malloc(sizeof(char *) * (scene->height + 1));
    copy_map = malloc(sizeof(char *) * (scene->height + 1));
    if (!scene->map || !copy_map)
        exit_error("Error: Memory allocation for map failed.");

    for (int j = 0; j < (scene->height + 1); j++) {
        scene->map[j] = NULL;
        copy_map[j] = NULL;
    }
    while (i <= scene->end)
    {
        process_line(scene, i, &num_players, copy_map);
        i++;
    }
   
    flood_fill(copy_map, scene, scene->player_x, scene->player_y, 0);

    //para printear el flood fill
    for (int i = 0; i < (scene->height); i++)
        printf("%s\n", copy_map[i]);
    
    if (!is_valid_map(scene, copy_map))
    {
        free_map(copy_map);
        exit_error("Error: Map is not closed.");
    }

    parse_map_errors(num_players);

    free_map(copy_map);
}

void parse_scene_file(const char *filename, t_map *scene)
{
    int lines_count;
    int i;

    lines_count = get_lines_count(filename);
    set_file_lines(filename, scene, lines_count);
    i = 0;
    while (scene->lines[i] != NULL)
    {
        if (scene->textures.north && scene->textures.south && scene->textures.west
            && scene->textures.east && scene->textures.ceiling_color[0] != -1 
            && scene->textures.floor_color[0] != -1)
            find_delimiter(scene->lines[i], i, scene);
        else
            parse_main_textures(scene->lines[i], scene);
        i++;
    }
    parse_map(scene);

    if (!scene->textures.north || !scene->textures.south || !scene->textures.west
        || !scene->textures.east)
    {
        free_scene(&scene);
        exit_error("Error: Missing one or more textures.");
    }
    if (scene->textures.floor_color[0] == -1 || scene->textures.ceiling_color[0] == -1)
    {
        free_scene(&scene);
        exit_error("Error: Missing floor or ceiling color.");
    }
}