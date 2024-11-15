/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:52:58 by kali              #+#    #+#             */
/*   Updated: 2024/11/11 15:06:38 by youness          ###   ########.fr       */
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
		 ft_errorv2(&cub->parse ,"Error : the image is not loaded\n");
}

static void	init_mlx(t_cub *mlx)
{
	mlx->var.s_w = WIN_W;
	mlx->var.s_h = WIN_H;
	mlx->mlxp = mlx_init();
	if (!mlx->mlxp)
		ft_errorv2(&mlx->parse ,"Error : mlx pointer\n");
	mlx->img.img = mlx_new_image(mlx->mlxp, mlx->var.s_w, mlx->var.s_h);
	if (!mlx->img.img)
		ft_errorv2(&mlx->parse ,"Error : the image is not loaded\n");
	mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
	if (!mlx->mlx_w)
	{
		ft_errorv2(&mlx->parse ,"Error : mlx pointer\n");
		// exit(1);
	}
	init_image(mlx);
}

static void	load_texture(t_cub *cub, t_img *texture, char *file_path)
{
	printf("\t%s\n", cub->parse.NO);
	texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w,
			&texture->h);
	if (!texture->img)
	{
		ft_errorv2(&cub->parse ,"Error: Could not load texture");
		// i need to destroy image that load before
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->len, &texture->endian);
}

static void	init_textures(t_cub *cub)
{
	printf(RED "`%s'\n" RES, cub->parse.NO);
	load_texture(cub, &cub->textures[0], cub->parse.NO);
	load_texture(cub, &cub->textures[1], cub->parse.EA);
	load_texture(cub, &cub->textures[2], cub->parse.WE);
	load_texture(cub, &cub->textures[3], cub->parse.SO);
	// load_texture(cub, &cub->textures[4], "./Assets/Textures/pestol.xpm");
}

int _close_window(t_cub *cub)
{
	int i = 0;

	while (i < 4)
	{
		mlx_destroy_image(cub->mlxp, cub->textures[i].img);
		i++;
	}
    mlx_destroy_window(cub->mlxp, cub->mlx_w);
    ft_exit(&cub->parse);
	return (0);
}

//!! Youness you need to handle the extention .cub name if i gave you .cub.cub 
void	init_engin(t_cub *cub, char *file)
{
	cub->parse.file_path = file;
	cub->parse.info = cub;
	parser(&cub->parse);
	init_map(cub, file);
	init_plyr(cub);
	init_mlx(cub);
	init_textures(cub);
	mlx_hook(cub->mlx_w, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, &key_release, cub);
    mlx_hook(cub->mlx_w, 17, 0, &_close_window, cub);
	mlx_loop_hook(cub->mlxp, &main_loop, cub);
	if (!cub->mlxp || !cub->mlx_w)
		ft_errorv2(&cub->parse ,"Error: Failed to initialize MLX.");
	mlx_loop(cub->mlxp);
}
