#include "../inc/cub3d.h"

static int extract_texture_path(const char *trimmed, char *result)
{
    int i;
    int in_quotes;
    int result_len;

    i = 0;
    in_quotes = 0;
    result_len = 0;
    ft_bzero(result, MAX_LINE_LEN);
    while (trimmed[i] != '\0')
    {
        if (trimmed[i] == '"')
            in_quotes = !in_quotes;
        else if (in_quotes || !ft_isspace(trimmed[i]))
        {
            if (result_len < MAX_LINE_LEN - 1)
                result[result_len++] = trimmed[i];
            else
                exit_error("Error: Texture path is too long.");
        }
        else
            exit_error("Error: Found a space in the file.");
        i++;
    }
    result[result_len] = '\0';
    return (in_quotes);
}

static void validate_and_assign_texture_path(const char *result,
    char **destination)
{
    if (*destination != NULL)
        exit_error("Error: Duplicate texture identifier.");
    *destination = ft_strdup(result);
    if (*destination == NULL)
        exit_error("Error: Memory allocation failed for texture path.");
}

static void parse_texture(char *line, const char *identifier, char **destination)
{
    int is_in_quotes;
    char *trimmed;
    char result[MAX_LINE_LEN];

    trimmed = trim_whitespace(line + ft_strlen(identifier));
    is_in_quotes = extract_texture_path(trimmed, result);
    if (is_in_quotes)
        exit_error("Error: Unmatched quotes in texture path.");
    validate_and_assign_texture_path(result, destination);
}


static void parse_color(char *line, const char *identifier, int *color)
{
    char *trimmed;
    int i;
    int num;

    i = 0;
    trimmed = trim_whitespace(line + ft_strlen(identifier));
    while (*trimmed != '\0' && i < 3)
    {
        while (ft_isspace(*trimmed))
            trimmed++;
        if (ft_isdigit(*trimmed))
        {
            num = 0;
            while (ft_isdigit(*trimmed))
                num = num * 10 + (*trimmed++ - '0');
            if (num > 255)
                exit_error("Error: Color values must be in range [0,255].");
            color[i++] = num;
        }
        else if (*trimmed++ != ',')
            exit_error("Error: Invalid color format.");
    }
    if ((*trimmed != '\0' && !ft_isspace(*trimmed)) || i != 3)
        exit_error("Error: Invalid color format.");
}

void parse_main_textures(char *line, t_map *scene)
{
    char *trimmed;
    
    trimmed = trim_whitespace(line);
    if (*trimmed == '\0')
    {
        free(trimmed);
        return;
    }
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
        parse_texture(trimmed, "NO", &scene->textures.north);
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
        parse_texture(trimmed, "SO", &scene->textures.south);
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
        parse_texture(trimmed, "WE", &scene->textures.west);
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
        parse_texture(trimmed, "EA", &scene->textures.east);
    else if (ft_strncmp(trimmed, "F ", 2) == 0)
        parse_color(trimmed, "F", scene->textures.floor_color);
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
        parse_color(trimmed, "C", scene->textures.ceiling_color);
    else if (!is_strspace(trimmed))
        exit_error("Error: Invalid identifier in scene file.");
    free(trimmed);
}