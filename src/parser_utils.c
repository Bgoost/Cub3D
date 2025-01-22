#include "../inc/cub3d.h"

int get_lines_count(const char *filename)
{
    char *line;
    int lines_count;
    int fd;
    fd = open(filename, O_RDONLY);
    lines_count = 0;
    if (fd < 0)
        exit_error("Error: Failed to open file.");
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
    scene->lines = malloc(sizeof(char *) * lines_count);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        exit_error("Error: Failed to open file.");
    i = 0;
    line = get_next_line(fd);
    while(line != NULL)
    {
        scene->lines[i] = line;
        line = get_next_line(fd);
        i++;
    }
    scene->lines[i] = NULL;
    close(fd);
}

int is_valid_map_char(char c)
{
    return c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W';
}

char *trim_whitespace(char *str)
{
    char *end;
    while (ft_isspace(*str))
        str++;
    if (*str == 0)
        return str; // All spaces

    end = str + ft_strlen(str) - 1;
    while (end > str && ft_isspace(*end))
        end--;

    end[1] = '\0';
    return str;
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

void free_scene(t_map *scene)
{
    free(scene->textures.north);
    free(scene->textures.south);
    free(scene->textures.west);
    free(scene->textures.east);
    // for (int i = 0; i < scene->width; i++) {
    //     free(scene->map[i]);
    // }
    free(scene->map);
}