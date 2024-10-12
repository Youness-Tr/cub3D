/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:56:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 11:06:07 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Header/cub3d.h"


void init_map(t_cub *cub, char *file)
{
    (void)file;
    cub->map.map2d = cub->parse.map;
    if (!cub->map.map2d)
    {
        ft_error("Error: Could not load map");
        exit(1);
    }
    cub->map.map_h = cub->parse.lines;
    cub->map.map_w = cub->parse.map_len;
    cub->map.posx = cub->parse.player_Y;
    cub->map.posy = cub->parse.player_x;
    printf("\t(%d, %d)\n",cub->map.posx, cub->map.posy);//Remove
}

void init_plyr(t_cub *cub)
{
    cub->plyr.plyr_x = cub->map.posx * TILE_SIZE + TILE_SIZE / 2;
    cub->plyr.plyr_y = cub->map.posy * TILE_SIZE + TILE_SIZE / 2;
    cub->plyr.angle = 0; //(90 * PI) / 180;
    cub->plyr.rot = 0.1;
    cub->plyr.fov_rd = (FOV * PI) / 180;
}

void init_image(t_cub *cub)
{
    t_img *imge;
    imge = &cub->img;
    imge->gme = cub;
    cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len, &imge->endian);
}


void init_mlx(t_cub *mlx)
{
    // int s_w;
    // int s_h;

    mlx->var.s_w = mlx->map.map_w * TILE_SIZE;
    mlx->var.s_h = mlx->map.map_h * TILE_SIZE;
    mlx->mlxp = mlx_init();
    mlx->img.img = mlx_new_image(mlx->mlxp,  mlx->var.s_w, mlx->var.s_h);
    mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
    init_image(mlx);
    // render_2d(mlx);
}

void init_engin(t_cub *cub, char *file)
{
    cub->parse.file_path = file;
    parser(&cub->parse);
    init_map(cub, file); //
    init_plyr(cub);
    init_mlx(cub);
    mlx_hook(cub->mlx_w, 2, 1L<<0, &mv, cub);
    mlx_loop(cub->mlxp);
}
int main(int ac, char **av)
{
    t_cub cub;

    if (ac != 2)
        ft_error("Error: ./cub3D Assets/maps/file.cub");
    init_engin(&cub, av[1]);
    return (0);
}
