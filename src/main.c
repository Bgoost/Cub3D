#include "../inc/cub3d.h"

void print_error(char* msg)
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
}