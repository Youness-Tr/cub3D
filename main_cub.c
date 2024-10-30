/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:56:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/30 18:34:07 by kali             ###   ########.fr       */
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
    // printf("\t(%d, %d)\n",cub->map.posx, cub->map.posy);//Remove
}

void init_plyr(t_cub *cub)
{
    cub->plyr.plyr_x = cub->map.posx * TILE_SIZE + TILE_SIZE / 2;
    cub->plyr.plyr_y = cub->map.posy * TILE_SIZE + TILE_SIZE / 2;
    cub->plyr.angle = (90 * PI) / 180;
    cub->plyr.rot = 0.1;
    cub->plyr.fov_rd = (FOV * PI) / 180;

    printf(RED "\t plyr_x :: %d, plyr_y :: %d\n\t angle :: %f fov_rd :: %f" RES,
           cub->plyr.plyr_x,
           cub->plyr.plyr_y,
           cub->plyr.angle,
           cub->plyr.fov_rd
        );
}

void init_image(t_cub *cub)
{
    t_img *imge;
    imge = &cub->img;
    imge->gme = cub;
    cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len, &imge->endian);
    if (!cub->img.img)
        ft_error("Error : the image is not loaded\n");
}

void init_mlx(t_cub *mlx)
{
    mlx->var.s_w = WIN_W; // mlx->map.map_w * TILE_SIZE;
    mlx->var.s_h = WIN_H; // mlx->map.map_h *TILE_SIZE;
    printf("\tsw :: %d, sh :: %d\n", mlx->var.s_w,mlx->var.s_h);
    mlx->mlxp = mlx_init();
    mlx->img.img = mlx_new_image(mlx->mlxp,  mlx->var.s_w, mlx->var.s_h);
    if (!mlx->img.img)
        ft_error("Error : the image is not loaded\n");
    mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
    init_image(mlx);
    // render_2d(mlx);
}

void load_texture(t_cub *cub, t_img *texture, char *file_path)
{
    texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w, &texture->h);
    if (!texture->img)
    {
        ft_error("Error: Could not load texture");
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->len, &texture->endian);
}

void init_textures(t_cub *cub)
{
    load_texture(cub, &cub->textures[0], "./Assets/Textures/walls.xpm");
    // load_texture(cub, &cub->textures[1], "./Assets/Textures/walls.xpm");
    // load_texture(cub, &cub->textures[2], "./Assets/Textures/walls.xpm");
    // load_texture(cub, &cub->textures[3], "./Assets/Textures/walls.xpm");
}


void init_engin(t_cub *cub, char *file)
{
    cub->parse.file_path = file;
    cub->parse.info = cub;
    parser(&cub->parse);
    init_map(cub, file); //
    init_plyr(cub);
    init_mlx(cub);
    init_textures(cub);
    // mlx_hook(cub->mlx_w, 2, 1L<<0, &mv, cub);
    mlx_hook(cub->mlx_w, 2, 1L << 0, &key_press, cub);
    mlx_hook(cub->mlx_w, 3, 1L<<1, &key_release, cub);
    mlx_loop_hook(cub->mlxp, &main_loop, cub);
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
