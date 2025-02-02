/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <martalop@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 19:08:06 by martalop          #+#    #+#             */
/*   Updated: 2024/09/10 14:30:47 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# include <unistd.h>
//# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		my_strchr(char *s);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*get_clean(char *stash);
char	*put_line(char *stash);
char	*read_file(char *buffer, char *stash, int read_result, int fd);
char	*free_strjoin(char *s1, char *s2);

#endif
