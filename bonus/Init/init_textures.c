/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:08:00 by youness           #+#    #+#             */
/*   Updated: 2024/11/26 18:40:52 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	load_texture(t_cub *cub, t_img *texture, char *file_path)
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

void init_gun_textures(t_cub *cub)
{
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
	
}

void init_door_textures(t_cub *cub)
{
	load_texture(cub, &cub->door[0], "./Assets/youness/door/frame_01.xpm");
	load_texture(cub, &cub->door[1], "./Assets/youness/door/frame_02.xpm");
	load_texture(cub, &cub->door[2], "./Assets/youness/door/frame_03.xpm");
	load_texture(cub, &cub->door[3], "./Assets/youness/door/frame_04.xpm");
	load_texture(cub, &cub->door[4], "./Assets/youness/door/frame_05.xpm");
	load_texture(cub, &cub->door[5], "./Assets/youness/door/frame_06.xpm");
	load_texture(cub, &cub->door[6], "./Assets/youness/door/frame_07.xpm");
	load_texture(cub, &cub->door[7], "./Assets/youness/door/frame_08.xpm");
	load_texture(cub, &cub->door[8], "./Assets/youness/door/frame_09.xpm");
	load_texture(cub, &cub->door[9], "./Assets/youness/door/frame_10.xpm");
	load_texture(cub, &cub->door[10], "./Assets/youness/door/frame_11.xpm");
	load_texture(cub, &cub->door[11], "./Assets/youness/door/frame_12.xpm");
	load_texture(cub, &cub->door[12], "./Assets/youness/door/frame_13.xpm");
	load_texture(cub, &cub->door[13], "./Assets/youness/door/frame_14.xpm");
	load_texture(cub, &cub->door[14], "./Assets/youness/door/frame_15.xpm");
	load_texture(cub, &cub->door[15], "./Assets/youness/door/frame_16.xpm");
	load_texture(cub, &cub->door[16], "./Assets/youness/door/frame_17.xpm");
	load_texture(cub, &cub->door[17], "./Assets/youness/door/frame_18.xpm");
	load_texture(cub, &cub->door[18], "./Assets/youness/door/frame_19.xpm");
	load_texture(cub, &cub->door[19], "./Assets/youness/door/frame_20.xpm");
	load_texture(cub, &cub->door[20], "./Assets/youness/door/frame_21.xpm");
}


void	init_textures(t_cub *cub)
{
	load_texture(cub, &cub->textures[0], cub->parse.no);
	load_texture(cub, &cub->textures[1], cub->parse.ea);
	load_texture(cub, &cub->textures[2], cub->parse.we);
	load_texture(cub, &cub->textures[3], cub->parse.so);
	load_texture(cub, &cub->textures[4], "./Assets/sprites/zoom.xpm");

	init_gun_textures(cub);
	init_door_textures(cub);
}

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
				o->doors[k].frame = 0;
				k++;
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
			}
			j++;
		}
		i++;
	}
}