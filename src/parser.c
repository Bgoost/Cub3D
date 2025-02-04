#include "../inc/cub3d.h"

void find_delimiter(char *line, int i, t_map *scene, int *empty_lines)
{
    int width;

    if (!is_strspace(line))
    {
        width = ft_strlen(line);
        if (line[width - 1] == '\n')
            width--;
        if (width > scene->width)
            scene->width = width;
        if (scene->start == 0)
        {
            scene->start = i;
            if (*empty_lines != 1)
            {
                free_scene(&scene);
                exit_error("Error:\nMore/Less than 1 empty line between textures and map");
            }
        }
    }
    else if (scene->start == 0)
        (*empty_lines)++;
    scene->end = i;
}

void errors_in_map(t_map *scene)
{
    if(scene->start == 0)
    {
        free_scene(&scene);
        exit_error("Error:\nNo map found.");
    }
    if (!scene->textures.north || !scene->textures.south || !scene->textures.west
        || !scene->textures.east)
    {
        free_scene(&scene);
        exit_error("Error:\nMissing one or more textures.");
    }
    if (scene->textures.floor_color[0] == -1 || scene->textures.ceiling_color[0] == -1)
    {
        free_scene(&scene);
        exit_error("Error:\nMissing floor or ceiling color.");
    }
}
void parse_scene_file(const char *filename, t_map *scene)
{
    int lines_count;
    int i;
    int empty_line;

    lines_count = get_lines_count(filename);
    set_file_lines(filename, scene, lines_count);
    empty_line = 0;
    i = 0;
    while (scene->lines[i] != NULL)
    {
        if (scene->textures.north && scene->textures.south && scene->textures.west
            && scene->textures.east && scene->textures.ceiling_color[0] != -1 
            && scene->textures.floor_color[0] != -1)
            {
                find_delimiter(scene->lines[i], i, scene, &empty_line);
                parse_main_textures(scene->lines[i], scene, 1);
            }
        else
            parse_main_textures(scene->lines[i], scene, 0);
        i++;
    }

    errors_in_map(scene);
    parse_map(scene);

}
