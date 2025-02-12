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
                exit_error("Error:\nTexture path is too long.");
        }
        else
            exit_error("Error:\nFound a space in the file.");
        i++;
    }
    result[result_len] = '\0';
    return (in_quotes);
}

static void validate_and_assign_texture_path(const char *result,
    char **destination)
{
    if (*destination != NULL)
        exit_error("Error:\nDuplicate texture identifier.");
    *destination = ft_strdup(result);
    if (*destination == NULL)
        exit_error("Error:\nMemory allocation failed for texture path.");
}

static void parse_texture(char *line, const char *identifier, char **destination)
{
    int is_in_quotes;
    char *trimmed;
    char result[MAX_LINE_LEN];

    trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
    is_in_quotes = extract_texture_path(trimmed, result);
    free(trimmed);
    if (is_in_quotes)
        exit_error("Error:\nUnmatched quotes in texture path.");
    validate_and_assign_texture_path(result, destination);
}


static void parse_number_and_comma(char **trimmed, int *color, int *i, int *comma_count)
{
    int num;

    while (ft_isspace(**trimmed))
        (*trimmed)++;
    if (ft_isdigit(**trimmed))
    {
        num = 0;
        while (ft_isdigit(**trimmed))
            num = num * 10 + (*(*trimmed)++ - '0');
        if (num > 255)
            exit_error("Error:\nColor values must be in range [0,255].");
        color[(*i)++] = num;
        while (ft_isspace(**trimmed))
            (*trimmed)++;
        if (**trimmed == ',')
        {
            (*comma_count)++;
            (*trimmed)++;
        }
        else if (**trimmed != '\0' && *i < 3)
            exit_error("Error:\nInvalid color format (missing commas).");
    }
    else
        exit_error("Error:\nInvalid color format (non-digit character found).");
}


static void parse_color(char *line, const char *identifier, int *color)
{
    char *trimmed;
    char *current;
    int i;
    int comma_count;

    i = 0;
    comma_count = 0;
    if(color[i] != -1)
        exit_error("Error:\nDuplicate color identifier.");
    trimmed = ft_strtrim(line + ft_strlen(identifier), " \t\n");
    current = trimmed;
    while (*current != '\0' && i < 3)
    {
        parse_number_and_comma(&current, color, &i, &comma_count);
    }
    if ((*current != '\0' && !ft_isspace(*current)) || i != 3 || comma_count != 2)
    {
        free(trimmed);
        exit_error("Error:\nInvalid color format.");
    }
    free(trimmed);

}


void parse_main_textures(char *line, t_map *scene, int map_started)
{
    char *trimmed;
    
    trimmed = ft_strtrim(line, " \t\n");
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
    else if (!is_strspace(trimmed) && !map_started)
    {
        printf("\033[31mError:\nInvalid texture identifier [%s] in file.\033[0m", trimmed);
        free(trimmed);
        exit_error("");
    }
    free(trimmed);
}
