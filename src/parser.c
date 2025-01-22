#include "../inc/cub3d.h"

// static void flood_fill(char **map, bool **visited, int rows, int cols, int x, int y) {
//     // Check bounds
//     if (x < 0 || y < 0 || x >= rows || y >= cols) return;
//     if (visited[x][y]) return;
    
//     // Check for wall ('1') or visited cells
//     if (map[x][y] == '1') return;
    
//     // Mark this cell as visited
//     visited[x][y] = true;

//     // Recursively fill neighboring cells
//     flood_fill(map, visited, rows, cols, x + 1, y);  // Down
//     flood_fill(map, visited, rows, cols, x - 1, y);  // Up
//     flood_fill(map, visited, rows, cols, x, y + 1);  // Right
//     flood_fill(map, visited, rows, cols, x, y - 1);  // Left
// }


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

void process_line(t_map *scene, int i, int *num_players)
{
    int j;
    
    j = 0;
    scene->map[i - scene->start] = strdup(ft_strtrim(scene->lines[i], "\n"));
    if (!scene->map[i - scene->start])
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
        j++;
    }
}

void parse_map(t_map *scene)
{
    int i;
    int num_players;
    
    i = scene->start;
    num_players = 0;
    scene->map = malloc(sizeof(char *) * (scene->end - scene->start + 1));
    if (!scene->map)
        exit_error("Error: Memory allocation for map failed.");
    while (i <= scene->end)
    {
        process_line(scene, i, &num_players);
        i++;
    }
    if (num_players == 0)
        exit_error("Error: No player position found.");
    if (num_players > 1)
        exit_error("Error: Multiple player positions found.");
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
        if(scene->textures.north && scene->textures.south && scene->textures.west
            && scene->textures.east && scene->textures.ceiling_color[0] != -1 
            && scene->textures.floor_color[0] != -1)
            find_delimiter(scene->lines[i], i, scene);
        else
            parse_main_textures(scene->lines[i], scene);
        i++;
    }
    parse_map(scene);

    printf("player_x: %d\n", scene->player_x);
    printf("player_y: %d\n", scene->player_y);
    printf("player_c: %c\n", scene->player_c);
    if (!scene->textures.north || !scene->textures.south || !scene->textures.west
        || !scene->textures.east)
        exit_error("Error: Missing one or more textures.");
    if (scene->textures.floor_color[0] == -1 || scene->textures.ceiling_color[0] == -1)
        exit_error("Error: Missing floor or ceiling color.");
}