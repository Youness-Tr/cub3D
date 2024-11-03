/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:52:58 by kali              #+#    #+#             */
/*   Updated: 2024/11/01 18:34:14 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"


static void init_image(t_cub *cub)
{
    t_img *imge;
    imge = &cub->img;
    imge->gme = cub;
    cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len, &imge->endian);
    if (!cub->img.img)
        ft_error("Error : the image is not loaded\n");
}

static void init_mlx(t_cub *mlx)
{
    mlx->var.s_w = WIN_W; // mlx->map.map_w * TILE_SIZE;
    mlx->var.s_h = WIN_H; // mlx->map.map_h *TILE_SIZE;
    mlx->mlxp = mlx_init();
    if (!mlx->mlxp)
    {
        ft_error("Error : mlx pointer\n");
        exit(1);
    }
    mlx->img.img = mlx_new_image(mlx->mlxp, mlx->var.s_w, mlx->var.s_h);
    if (!mlx->img.img)
        ft_error("Error : the image is not loaded\n");
    mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
    if (!mlx->mlx_w)
    {
        ft_error("Error : mlx pointer\n");
        exit(1);
    }
    init_image(mlx);
}


static void load_texture(t_cub *cub, t_img *texture, char *file_path)
{
     printf("\t%s\n",cub->parse.NO);
    texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w, &texture->h);
    if (!texture->img)
    {
        ft_error("Error: Could not load texture");
        exit(1); // free hnaya
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->len, &texture->endian);
}

static void init_textures(t_cub *cub)
{
    load_texture(cub, &cub->textures[0], "./Assets/Textures/wall_3.xpm");
    load_texture(cub, &cub->textures[1], "./Assets/Textures/wall_3.xpm");
    load_texture(cub, &cub->textures[2], "./Assets/Textures/wall_3.xpm");
    load_texture(cub, &cub->textures[3], "./Assets/Textures/wall_3.xpm");
    // load_texture(cub, &cub->textures[1], "./Assets/Textures/bookshelf.xpm");
    // load_texture(cub, &cub->textures[2], "./Assets/Textures/blue_pone.xpm");
    // load_texture(cub, &cub->textures[3], "./Assets/Textures/bricks.xpm");

}

void init_engin(t_cub *cub, char *file)
{
    cub->parse.file_path = file;
    cub->parse.info = cub;
    parser(&cub->parse);
    init_map(cub, file);
    init_plyr(cub);
    init_mlx(cub);
    init_textures(cub);
    cub->move_forward = 0;
    cub->move_backward = 0;
    cub->move_left = 0;
    cub->move_right = 0;
    cub->rotate_left = 0;
    cub->rotate_right = 0;
    mlx_hook(cub->mlx_w, 2, 1L << 0, &key_press, cub);
    mlx_hook(cub->mlx_w, 3, 1L<<1, &key_release, cub);
    mlx_loop_hook(cub->mlxp, &main_loop, cub);

    mlx_loop(cub->mlxp);
}
