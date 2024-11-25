/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:52:58 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 17:05:16 by youness          ###   ########.fr       */
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

static void	load_texture(t_cub *cub, t_img *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w,
			&texture->h);
	if (!texture->img)
	{
		ft_errorv2(&cub->parse, "ERROR: FAILED TO LOAD TEXTURE !");
		_close_window(cub);
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
	///home/kali/Desktop/Cub/bonus/Assets/sprites/portal.xpm
	// /Users/ajabri/Desktop/cub/bonus/Assets/Textures/wepon.xpm
	load_texture(cub, &cub->textures[4], "./Assets/youness/door/frame_01.xpm");
	load_texture(cub, &cub->textures[5], "./Assets/sprites/zoom.xpm");
	load_texture(cub, &cub->textures[6], "./Assets/sprites/barrel_wolf.xpm");
	load_texture(cub, &cub->textures[7], "./Assets/youness/door/frame_21.xpm");
	// load_texture(cub, &cub->textures[10], "./Assets/sprites/barrel_wolf.xpm");
// Assets/youness/door/frame_01.xpm
	// load_texture(cub, &cub->gun[0], "./Assets/youness/door/frame_00.xpm");
	// load_texture(cub, &cub->gun[1], "./Assets/youness/door/frame_01.xpm");
	// load_texture(cub, &cub->gun[2], "./Assets/youness/door/frame_02.xpm");
	load_texture(cub, &cub->gun[0], "./Assets/youness/gun_two/frame_03.xpm");
	load_texture(cub, &cub->gun[1], "./Assets/youness/gun_two/frame_04.xpm");
	load_texture(cub, &cub->gun[2], "./Assets/youness/gun_two/frame_05.xpm");
	load_texture(cub, &cub->gun[3], "./Assets/youness/gun_two/frame_06.xpm");
	load_texture(cub, &cub->gun[4], "./Assets/youness/gun_two/frame_07.xpm");
	load_texture(cub, &cub->gun[5], "./Assets/youness/gun_two/frame_08.xpm");
	load_texture(cub, &cub->gun[6], "./Assets/youness/gun_two/frame_09.xpm");
	load_texture(cub, &cub->gun[7], "./Assets/youness/gun_two/frame_10.xpm");
	load_texture(cub, &cub->gun[8], "./Assets/youness/gun_two/frame_11.xpm");
	load_texture(cub, &cub->gun[9], "./Assets/youness/gun_two/frame_12.xpm");
	load_texture(cub, &cub->gun[10], "./Assets/youness/gun_two/frame_13.xpm");
	load_texture(cub, &cub->gun[11], "./Assets/youness/gun_two/frame_14.xpm");
	load_texture(cub, &cub->gun[12], "./Assets/youness/gun_two/frame_15.xpm");
	load_texture(cub, &cub->gun[13], "./Assets/youness/gun_two/frame_16.xpm");
	load_texture(cub, &cub->gun[14], "./Assets/youness/gun_two/frame_17.xpm");
	load_texture(cub, &cub->gun[15], "./Assets/youness/gun_two/frame_18.xpm");
	load_texture(cub, &cub->gun[16], "./Assets/youness/gun_two/frame_19.xpm");
	load_texture(cub, &cub->gun[17], "./Assets/youness/gun_two/frame_20.xpm");
	load_texture(cub, &cub->gun[18], "./Assets/youness/gun_two/frame_21.xpm");
	//////////////////////////////////////////////
	load_texture(cub, &cub->door[1], "./Assets/youness/door/frame_01.xpm");
	load_texture(cub, &cub->door[2], "./Assets/youness/door/frame_02.xpm");
	load_texture(cub, &cub->door[3], "./Assets/youness/door/frame_03.xpm");
	load_texture(cub, &cub->door[4], "./Assets/youness/door/frame_04.xpm");
	load_texture(cub, &cub->door[5], "./Assets/youness/door/frame_05.xpm");
	load_texture(cub, &cub->door[6], "./Assets/youness/door/frame_06.xpm");
	load_texture(cub, &cub->door[7], "./Assets/youness/door/frame_07.xpm");
	load_texture(cub, &cub->door[8], "./Assets/youness/door/frame_08.xpm");
	load_texture(cub, &cub->door[9], "./Assets/youness/door/frame_09.xpm");
	load_texture(cub, &cub->door[10], "./Assets/youness/door/frame_10.xpm");
	load_texture(cub, &cub->door[11], "./Assets/youness/door/frame_11.xpm");
	load_texture(cub, &cub->door[12], "./Assets/youness/door/frame_12.xpm");
	load_texture(cub, &cub->door[13], "./Assets/youness/door/frame_13.xpm");
	load_texture(cub, &cub->door[14], "./Assets/youness/door/frame_14.xpm");
	load_texture(cub, &cub->door[15], "./Assets/youness/door/frame_15.xpm");
	load_texture(cub, &cub->door[16], "./Assets/youness/door/frame_16.xpm");
	load_texture(cub, &cub->door[17], "./Assets/youness/door/frame_17.xpm");
	load_texture(cub, &cub->door[18], "./Assets/youness/door/frame_18.xpm");
	load_texture(cub, &cub->door[19], "./Assets/youness/door/frame_19.xpm");
	load_texture(cub, &cub->door[20], "./Assets/youness/door/frame_20.xpm");
	load_texture(cub, &cub->door[21], "./Assets/youness/door/frame_21.xpm");
	// load_texture(cub, &cub->gun[3], "./Assets/sprites/w3.xpm");

}

/*
//! Remove this function later
 */

void get_doors_cordn(t_cub *o)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (i < o->map.map_h)
	{
		j = 0;
		while (j < o->map.map_w)
		{
			if (o->map.map2d[i][j] == 'D')
			{
				o->doors[k].x = j * TILE_SIZE;
				o->doors[k].y = i * TILE_SIZE;
				o->doors[k].open = 0;
				o->doors[k].frame = 1;
				k++;
				// break;
			}
			j++;
		}
		i++;
	}
}


void ndoors(t_cub *o)
{
	int i;
	int j;

	i = 0;
	while (i < o->map.map_h)
	{
		j = 0;
		while (j < o->map.map_w)
		{
			if (o->map.map2d[i][j] == 'D')
			{
				o->ndoors++;
				// break;
			}
			j++;
		}
		i++;
	}
}

void init_door(t_cub *cub)
{

	cub->ndoors = 0;
	cub->index = 0;
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
	// mlx_do_sync(cub->mlxp);
	if (!cub->mlxp || !cub->mlx_w)
		ft_errorv2(&cub->parse, "Error: FIALED TO INITALIZE MLX.");
	mlx_loop(cub->mlxp);
}
