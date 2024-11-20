/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:52:58 by kali              #+#    #+#             */
/*   Updated: 2024/11/20 10:22:55 by ajabri           ###   ########.fr       */
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
		ft_errorv2(&cub->parse, "Error : the image is not loaded\n");
}

static void	init_mlx(t_cub *mlx)
{
	mlx->var.s_w = WIN_W;
	mlx->var.s_h = WIN_H;
	mlx->mlxp = mlx_init();
	if (!mlx->mlxp)
		ft_errorv2(&mlx->parse, "Error : mlx pointer\n");
	mlx->img.img = mlx_new_image(mlx->mlxp, mlx->var.s_w, mlx->var.s_h);
	if (!mlx->img.img)
		ft_errorv2(&mlx->parse, "Error : the image is not loaded\n");
	mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
	if (!mlx->mlx_w)
		ft_errorv2(&mlx->parse, "Error : mlx pointer\n");
	init_image(mlx);
}

static void	load_texture(t_cub *cub, t_img *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w,
			&texture->h);
	if (!texture->img)
	{
		ft_errorv2(&cub->parse, "Error: Could not load texture");
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
	load_texture(cub, &cub->textures[4], "./Assets/sprites/metal_door_close.xpm");
	load_texture(cub, &cub->textures[5], "./Assets/sprites/zoom.xpm");
	load_texture(cub, &cub->textures[6], "./Assets/sprites/cover.xpm");
	load_texture(cub, &cub->textures[7], "./Assets/sprites/metal_door_op.xpm");
	// load_texture(cub, &cub->textures[10], "./Assets/sprites/barrel_wolf.xpm");
	load_texture(cub, &cub->gun[0], "./Assets/sprites/w0.xpm");
	load_texture(cub, &cub->gun[1], "./Assets/sprites/w1.xpm");
	load_texture(cub, &cub->gun[2], "./Assets/sprites/w2.xpm");
	load_texture(cub, &cub->gun[3], "./Assets/sprites/w4.xpm");
	load_texture(cub, &cub->gun[4], "./Assets/sprites/w5.xpm");
	load_texture(cub, &cub->gun[5], "./Assets/sprites/w6.xpm");
	// load_texture(cub, &cub->gun[3], "./Assets/sprites/w3.xpm");
	
}

/*
//! Remove this function later
 */

void find_door_cordn(t_cub *o)
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
				o->door.x = j;
				o->door.y = i;
				break;
			}
			j++;
		}
		i++;
	}
}

void init_door(t_cub *cub)
{
	find_door_cordn(cub);
	cub->door.open = 0;
	cub->gun_frame = 0;
	cub->door.frame = 4;
}


void	init_engin(t_cub *cub, char *file)
{
	cub->parse.file_path = file;
	cub->parse.info = cub;
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
		ft_errorv2(&cub->parse, "Error: Failed to initialize MLX.");
	mlx_loop(cub->mlxp);
}
