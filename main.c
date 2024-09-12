/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/11 11:28:31 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

int main(int ac, char **av)
{

    void *mlx;
    void *mlx_win;
    mlx = mlx_init();
    int i = 0;
    int j = 0;
    mlx_win = mlx_new_window(mlx, WIN_W, WIN_H, "CUB");

    void *img = mlx_xpm_file_to_image(mlx, );
    // while (i < WIN_H)
    // {
    //     j = 0;
    //     while (j < WIN_W)
    //     {
    //         mlx_pixel_put(mlx, mlx_win, i, j,54512);
    //         j++;
    //     }
    //     i++;
    // }
    mlx_loop(mlx);

    return (0);
}
