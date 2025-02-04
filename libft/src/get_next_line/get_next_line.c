/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:57:21 by martalop          #+#    #+#             */
/*   Updated: 2024/09/10 14:39:05 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	indx;

	indx = 0;
	while (s[indx] != '\0')
		indx++;
	return (indx);
}

char	*get_clean(char *stash)
{
	char	*str;
	int		i;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	str = ft_substr_gnl(stash, i, (ft_strlen_gnl(stash) - i));
	free(stash);
	if (!str)
		return (NULL);
	return (str);
}

char	*put_line(char *stash)
{
	int		i;
	char	*s;

	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0' )
		i++;
	if (stash[i] == '\n')
		i++;
	s = ft_substr_gnl(stash, 0, i);
	if (!s)
		return (NULL);
	return (s);
}

char	*read_file(char *buffer, char *stash, int read_result, int fd)
{
	if (stash == NULL)
	{
		stash = ft_strdup_gnl("");
		if (!stash)
			return (free(buffer), NULL);
	}
	while (my_strchr(stash) == 0 && read_result != 0)
	{
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result < 0)
			return (free(buffer), free(stash), NULL);
		else if (read_result == 0)
			break ;
		buffer[read_result] = '\0';
		stash = free_strjoin(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	if (stash[0] == '\0' && read_result == 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*stash;
	int			read_result;
	// int			i;

	// i = 0;
	if (fd < 0 || BUFFER_SIZE < 1 || fd > 10240)
		return (NULL);
	read_result = -1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(stash), stash = NULL, NULL);
	stash = read_file(buffer, stash, read_result, fd);
	if (!stash)
		return (NULL);
	line = put_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = get_clean(stash);
	if (!stash)
		return (free(line), NULL);
	return (line);
}

// int	main(void)
// {
// 	int	fd;
// 	char	*str;;
// 	int	i;

// 	i = 1;
// 	fd = open("infile", O_RDWR);
// //	printf("%d\n", fd);
// 	str = get_next_line(fd);
// 	while (str != NULL)
// 	{
// 		printf("line %d: %s", i, str);
// 		free(str);
// 		str = get_next_line(fd);
// 		i++;
// 		if (str == NULL)
// 			printf("line %d: %s", i, str);
// 	}
// 	close(fd);
// 	return (0);
// }
