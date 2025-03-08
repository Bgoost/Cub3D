/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 parser_utils.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/02/13 19:26:29 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2025/02/13 19:26:29 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	get_lines_count(const char *filename)
{
	char	*line;
	int		lines_count;
	int		fd;

	fd = open(filename, O_RDONLY);
	lines_count = 0;
	if (fd < 0)
		exit_error("Error:\nFailed to open file.\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		lines_count++;
	}
	close(fd);
	return (lines_count);
}

static void	read_file_lines(int fd, t_map *scene)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		scene->lines[i] = ft_strdup(line);
		if (!scene->lines[i])
		{
			free(line);
			exit_error("Memory allocation error.\n");
		}
		free(line);
		line = get_next_line(fd);
		i++;
	}
	scene->lines[i] = NULL;
}

void	set_file_lines(const char *filename, t_map *scene, int lines_count)
{
	int	fd;

	scene->lines = malloc(sizeof(char *) * (lines_count + 1));
	if (!scene->lines)
	{
		free_scene(&scene);
		exit_error("Memory allocation error.\n");
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free_scene(&scene);
		exit_error("Error:\nFailed to open file.\n");
	}
	read_file_lines(fd, scene);
	close(fd);
}

// void	set_file_lines(const char *filename, t_map *scene, int lines_count)
// {
//	int		i;
//	int		fd;
//	char	*line;

//	scene->lines = malloc(sizeof(char *) * (lines_count + 1));
//	if (!scene->lines)
//	{
//		free_scene(&scene);
//		exit_error("Memory allocation error");
//	}
//	fd = open(filename, O_RDONLY);
//	if (fd < 0)
//		exit_error("Error:\nFailed to open file.");
//	i = 0;
//	line = get_next_line(fd);
//	while (line != NULL)
//	{
//		scene->lines[i] = ft_strdup(line);
//		if (!scene->lines[i])
//			exit_error("Memory allocation error");
//		free(line);
//		line = get_next_line(fd);
//		i++;
//	}
//	scene->lines[i] = NULL;
//	close(fd);
// }

int	is_notvalid(char *str)
{
	int	i;
	int	notvalid;

	i = 0;
	notvalid = 0;
	while (str[i])
	{
		if (!ft_strchr(VALID_MAP_CHARS, str[i]))
			notvalid++;
		i++;
	}
	if (notvalid > 1)
		return (0);
	return (1);
}

int	is_strspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}
