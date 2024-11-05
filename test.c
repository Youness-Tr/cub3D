#include <stdlib.h>
#include "mlx/mlx.h"

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bpp;        // Bytes per pixel
    int     size_line;  // Size of a line
    int     endian;     // Endianness
} t_data;

void    mlx_put_pixel(t_data *data, int x, int y, int color) {
    if (x < 0 || x >= 800 || y < 0 || y >= 600) // Check bounds
        return;
    char    *dst;

    dst = data->img_data + (y * data->size_line + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

int main() {
    t_data data;

    data.mlx_ptr = mlx_init();
    data.win_ptr = mlx_new_window(data.mlx_ptr, 800, 600, "Example");
    data.img_ptr = mlx_new_image(data.mlx_ptr, 800, 600);
    data.img_data = mlx_get_data_addr(data.img_ptr, &data.bpp, &data.size_line, &data.endian);

    // Example: Draw a red pixel at (100, 100)
    for (int i = 0; i < 800; i++)
        mlx_put_pixel(&data, i, i, 0x00FF0000);

    mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img_ptr, 0, 0);
    mlx_loop(data.mlx_ptr);

    // Clean up
    mlx_destroy_image(data.mlx_ptr, data.img_ptr);
    mlx_destroy_window(data.mlx_ptr, data.win_ptr);
    free(data.mlx_ptr); // Note: mlx_ptr should not be freed like this; it's managed by MiniLibX

    return 0;
}