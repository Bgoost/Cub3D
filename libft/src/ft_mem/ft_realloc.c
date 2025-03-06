/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 ft_realloc.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: crmanzan <crmanzan@student.42barcel>		+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2024/05/10 21:20:40 by crmanzan		   #+#	  #+#			  */
/*	 Updated: 2024/05/10 22:23:55 by crmanzan		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */
#include "../../inc/libft.h"

// size_t	get_allocated_size(void *ptr)
// {
// 	t_mem_block	*block;

// 	if (ptr == NULL)
// 		return (0);
// 	block = (t_mem_block *)((char *)ptr - sizeof(size_t));
// 	return (block->size);
// }

// static void	*null_pointer(int new_size)
// {
// 	t_mem_block	*new_block;

// 	new_block = malloc(sizeof(size_t) + new_size);
// 	if (new_block == NULL)
// 		return (NULL);
// 	new_block->size = new_size;
// 	return (new_block->data);
// }

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	**from_copy;
	void	**buff_dir_mem;
	int		count_dir_mem;
	int		i;

	(void)new_size;
	count_dir_mem = 0;
	from_copy = (void **)ptr;
	while (ptr && from_copy[count_dir_mem])
		count_dir_mem += 1;
	buff_dir_mem = malloc(sizeof(void *) * (count_dir_mem + 1));
	if (!buff_dir_mem)
		return (NULL);
	i = 0;
	while (i < count_dir_mem)
	{
		buff_dir_mem[i] = from_copy[i];
		i++;
	}
	buff_dir_mem[i] = NULL;
	free(ptr);
	return ((void *)buff_dir_mem);
}
