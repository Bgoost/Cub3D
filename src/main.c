#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    mlx_t* mlx;

    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!mlx)
        return 1;
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return 0;
}