#include "MLX42-master/include/MLX42/MLX42.h"
#define WIDTH 1600
#define HEIGHT 1000

int main(int argc, char *argv)
{
    mlx_t* mlx;

    mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
    if (!mlx)
        return 1;
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return 0;
}