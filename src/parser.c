#include "../inc/cub3d.h"

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