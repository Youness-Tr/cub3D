/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:52:58 by kali              #+#    #+#             */
/*   Updated: 2024/11/26 18:08:12 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

static void	init_image(t_cub *cub)
{
	t_img	*imge;

	imge = &cub->img;
	imge->gme = cub;
	cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len,
			&imge->endian);
	if (!cub->img.img)
		ft_errorv2(&cub->parse, "ERROR : IMAGE NOT LOADED !!!\n");
}

static void	init_mlx(t_cub *mlx)
{
	mlx->var.s_w = WIN_W;
	mlx->var.s_h = WIN_H;
	mlx->mlxp = mlx_init();
	if (!mlx->mlxp)
		ft_errorv2(&mlx->parse, "ERROR : INITALIZE MLX\n");
	mlx->img.img = mlx_new_image(mlx->mlxp, mlx->var.s_w, mlx->var.s_h);
	if (!mlx->img.img)
		ft_errorv2(&mlx->parse, "ERROR : IMAGE NOT LOADED !!!\n");
	mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
	if (!mlx->mlx_w)
		ft_errorv2(&mlx->parse, "ERROR : MLX WINDOW\n");
	init_image(mlx);
}

void	init_door(t_cub *cub)
{
	cub->ndoors = 0;
	cub->default_door.open = -1;
	cub->default_door.frame = MAX_DOOR;
	ndoors(cub);
	if (cub->ndoors == 0)
		ft_errorv2(&cub->parse, "Error: NO DOORS IN THE MAP.");
	cub->doors = ft_malloc(cub, sizeof(t_door) * cub->ndoors);
	get_doors_cordn(cub);
}

void	init_engin(t_cub *cub, char *file)
{
	cub->parse.file_path = file;
	cub->parse.info = cub;
	cub->free = NULL;
	cub->gun_frame = 0;
	cub->is_shooting = 0;
	parser(&cub->parse);
	init_map(cub);
	init_plyr(cub);
	init_door(cub);
	init_mlx(cub);
	init_textures(cub);
	mlx_hook(cub->mlx_w, 2, 1L << 0, &key_press, cub);
	mlx_hook(cub->mlx_w, 3, 1L << 1, &key_release, cub);
	mlx_hook(cub->mlx_w, 4, 1L << 2, &mouse_press, cub);
	mlx_hook(cub->mlx_w, 5, 1L << 3, &mouse_release, cub);
	mlx_hook(cub->mlx_w, 17, 0, &_close_window, cub);
	mlx_loop_hook(cub->mlxp, &main_loop, cub);
	if (!cub->mlxp || !cub->mlx_w)
		ft_errorv2(&cub->parse, "Error: FIALED TO INITALIZE MLX.");
	mlx_loop(cub->mlxp);
}
