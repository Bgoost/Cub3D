/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crmanzan <crmanzan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:58:05 by crmanzan          #+#    #+#             */
/*   Updated: 2025/03/06 11:56:45 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <string.h>
# include "get_next_line.h"

typedef struct s_mem_block
{
	size_t	size;
	char	data[];
}			t_mem_block;

// LIBFT
void			ft_bzero(void *s, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_realloc(void *ptr, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strcpy(char *s1, char *s2);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *h, const char *n, size_t len);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_itoa(long n);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_memcmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
size_t			ft_strlcat(char *dest, char *src, size_t size);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
int				ft_isspace(char c);
void			free_words(char	**words);

#endif
