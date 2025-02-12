/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: martalop <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:07:39 by martalop          #+#    #+#             */
/*   Updated: 2025/02/03 22:39:24 by martalop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void exit_error(char* msg)
{
    printf("\033[31m%s\n\033[0m", msg);
    exit(1);
}

/*int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    t_map *map;
    if(!main_checker(argc, argv, &map))
        return 1;
    printf("All good, freeing map\n");
    free_scene(&map);
    return 0;

}*/

// lo dejo comentado por si acaso, si quieres lo borrass
/*void print_error(char *msg)
{
    printf("\033[41mError\033[0m\n");
    printf("\033[31m%s\n\033[0m", msg);
}

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    mlx_t* mlx;

    if (argc != 2)
        return (print_error("Usage: ./Cub3D Map_name.cub"), 1);

    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!mlx)
        return 1;
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return 0;
}*/
