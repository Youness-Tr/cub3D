/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:05:03 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/12/17 15:09:20 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

static void	init_image(t_cub *cub)
{
	t_img	*imge;

	imge = &cub->img;
	imge->gme = cub;
	cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len,
			&imge->endian);
	if (!cub->img.img)
		ft_errorv2(&cub->parse, "Error\n: IMAGE NOT LOADED !!!");
}

static void	init_mlx(t_cub *mlx)
{
	mlx->var.s_w = WIN_W;
	mlx->var.s_h = WIN_H;
	mlx->mlxp = mlx_init();
	if (!mlx->mlxp)
		ft_errorv2(&mlx->parse, "Error\n: INITALIZE MLX");
	mlx->img.img = mlx_new_image(mlx->mlxp, mlx->var.s_w, mlx->var.s_h);
	if (!mlx->img.img)
		ft_errorv2(&mlx->parse, "Error\n: IMAGE NOT LOADED !!!");
	mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
	if (!mlx->mlx_w)
		ft_errorv2(&mlx->parse, "Error\n: MLX WINDOW");
	init_image(mlx);
}

static void	load_texture(t_cub *cub, t_img *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w,
			&texture->h);
	if (!texture->img)
	{
		ft_errorv2(&cub->parse, "ERROR\n: FAILED TO LOAD TEXTURE !");
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->len, &texture->endian);
}

static void	init_textures(t_cub *cub)
{
	load_texture(cub, &cub->textures[0], cub->parse.no);
	load_texture(cub, &cub->textures[1], cub->parse.ea);
	load_texture(cub, &cub->textures[2], cub->parse.we);
	load_texture(cub, &cub->textures[3], cub->parse.so);
}

void	init_engin(t_cub *cub, char *file)
{
	cub->parse.file_path = file;
	cub->parse.info = cub;
	cub->free = NULL;
	parser(&cub->parse);
	init_map(cub);
	init_plyr(cub);
	init_mlx(cub);
	init_textures(cub);
	mlx_hook(cub->mlx_w, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, &key_release, cub);
	mlx_hook(cub->mlx_w, 17, 0, &_close_window, cub);
	mlx_loop_hook(cub->mlxp, &main_loop, cub);
	if (!cub->mlxp || !cub->mlx_w)
		ft_errorv2(&cub->parse, "Error\n: FIALED TO INITALIZE MLX.");
	mlx_loop(cub->mlxp);
}
