/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 19:03:24 by crmanzan          #+#    #+#             */
/*   Updated: 2024/05/10 21:14:48 by crmanzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(const char *s, unsigned int start, size_t len);
char	*get_next_line(int fd);
char	*free_all_gnl(char **storage);

//char    *get_line(char *storage);
//char    *get_storage(int fd, char *storage);
//char    *update_storage(char *storage);

#endif
