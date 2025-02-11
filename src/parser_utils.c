#include "../inc/cub3d.h"

int get_lines_count(const char *filename)
{
    char *line;
    int lines_count;
    int fd;
    fd = open(filename, O_RDONLY);
    lines_count = 0;
    if (fd < 0)
        exit_error("Error:\nFailed to open file.");
    line = get_next_line(fd);
    while(line != NULL)
    {
        free(line);
        line = get_next_line(fd);
        lines_count++;
    }
    close(fd);
    return lines_count;
}

void set_file_lines(const char *filename, t_map *scene, int lines_count)
{
    int i;
    int fd;
    char *line;
    char *tmp;

    scene->lines = malloc(sizeof(char *) * (lines_count + 1));
    if (!scene->lines)
        exit_error("Memory allocation error");
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_error("Error:\nFailed to open file.");
    i = 0;
    line = get_next_line(fd);
    while(line != NULL)
    {
        tmp = line;
        scene->lines[i] = ft_strdup(line);
        if (!scene->lines[i])
            exit_error("Memory allocation error");
        free(tmp);
        line = get_next_line(fd);
        i++;
    }
    scene->lines[i] = NULL;
    close(fd);
}

int is_notvalid(char *str)
{
    int i;
    int notvalid;

    i = 0;
    notvalid = 0;
    while (str[i])
    {
        if (!ft_strchr(VALID_MAP_CHARS, str[i]))
            notvalid++;
        i++;
    }
    if(notvalid > 1)
        return (0);
    return (1);
}


int is_strspace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}

void free_textures(t_textures *textures)
{
    if (textures->north)
    {
        free(textures->north);
        textures->north = NULL;
    }
    if (textures->south)
    {
        free(textures->south);
        textures->south = NULL;
    }
    if (textures->west)
    {
        free(textures->west);
        textures->west = NULL;
    }
    if (textures->east)
    {
        free(textures->east);
        textures->east = NULL;
    }
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

void free_scene(t_map **scene)
{
    if (!scene || !(*scene))
        return;

    free_textures(&(*scene)->textures);
    if ((*scene)->lines)
    {
        free_map((*scene)->lines);
        (*scene)->lines = NULL;
    }
    if ((*scene)->map)
    {
        free_map((*scene)->map);
        (*scene)->map = NULL;
    }
    free(*scene);
    *scene = NULL;
}
