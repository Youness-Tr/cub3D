/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:08:00 by youness           #+#    #+#             */
/*   Updated: 2024/12/13 15:07:44 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	load_texture(t_cub *cub, t_img *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(cub->mlxp, file_path, &texture->w,
			&texture->h);
	if (!texture->img)
	{
		ft_errorv2(&cub->parse, "Error\n FAILED TO LOAD TEXTURE !");
		_close_window(cub);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->len, &texture->endian);
}

void	init_gun_textures(t_cub *cub)
{
	load_texture(cub, &cub->gun[0], "./Assets/gun/frame_03.xpm");
	load_texture(cub, &cub->gun[1], "./Assets/gun/frame_04.xpm");
	load_texture(cub, &cub->gun[2], "./Assets/gun/frame_05.xpm");
	load_texture(cub, &cub->gun[3], "./Assets/gun/frame_06.xpm");
	load_texture(cub, &cub->gun[4], "./Assets/gun/frame_07.xpm");
	load_texture(cub, &cub->gun[5], "./Assets/gun/frame_08.xpm");
	load_texture(cub, &cub->gun[6], "./Assets/gun/frame_09.xpm");
	load_texture(cub, &cub->gun[7], "./Assets/gun/frame_10.xpm");
	load_texture(cub, &cub->gun[8], "./Assets/gun/frame_11.xpm");
	load_texture(cub, &cub->gun[9], "./Assets/gun/frame_12.xpm");
	load_texture(cub, &cub->gun[10], "./Assets/gun/frame_13.xpm");
	load_texture(cub, &cub->gun[11], "./Assets/gun/frame_14.xpm");
	load_texture(cub, &cub->gun[12], "./Assets/gun/frame_15.xpm");
	load_texture(cub, &cub->gun[13], "./Assets/gun/frame_16.xpm");
	load_texture(cub, &cub->gun[14], "./Assets/gun/frame_17.xpm");
	load_texture(cub, &cub->gun[15], "./Assets/gun/frame_18.xpm");
	load_texture(cub, &cub->gun[16], "./Assets/gun/frame_19.xpm");
	load_texture(cub, &cub->gun[17], "./Assets/gun/frame_20.xpm");
	load_texture(cub, &cub->gun[18], "./Assets/gun/frame_21.xpm");
}

void	init_door_textures(t_cub *cub)
{
	load_texture(cub, &cub->door[0], "./Assets/door/frame_01.xpm");
	load_texture(cub, &cub->door[1], "./Assets/door/frame_02.xpm");
	load_texture(cub, &cub->door[2], "./Assets/door/frame_03.xpm");
	load_texture(cub, &cub->door[3], "./Assets/door/frame_04.xpm");
	load_texture(cub, &cub->door[4], "./Assets/door/frame_05.xpm");
	load_texture(cub, &cub->door[5], "./Assets/door/frame_06.xpm");
	load_texture(cub, &cub->door[6], "./Assets/door/frame_07.xpm");
	load_texture(cub, &cub->door[7], "./Assets/door/frame_08.xpm");
	load_texture(cub, &cub->door[8], "./Assets/door/frame_09.xpm");
	load_texture(cub, &cub->door[9], "./Assets/door/frame_10.xpm");
	load_texture(cub, &cub->door[10], "./Assets/door/frame_11.xpm");
	load_texture(cub, &cub->door[11], "./Assets/door/frame_12.xpm");
	load_texture(cub, &cub->door[12], "./Assets/door/frame_13.xpm");
	load_texture(cub, &cub->door[13], "./Assets/door/frame_14.xpm");
	load_texture(cub, &cub->door[14], "./Assets/door/frame_15.xpm");
	load_texture(cub, &cub->door[15], "./Assets/door/frame_16.xpm");
	load_texture(cub, &cub->door[16], "./Assets/door/frame_17.xpm");
	load_texture(cub, &cub->door[17], "./Assets/door/frame_18.xpm");
	load_texture(cub, &cub->door[18], "./Assets/door/frame_19.xpm");
	load_texture(cub, &cub->door[19], "./Assets/door/frame_20.xpm");
	load_texture(cub, &cub->door[20], "./Assets/door/frame_21.xpm");
}

void	init_textures(t_cub *cub)
{
	load_texture(cub, &cub->textures[0], cub->parse.no);
	load_texture(cub, &cub->textures[1], cub->parse.ea);
	load_texture(cub, &cub->textures[2], cub->parse.we);
	load_texture(cub, &cub->textures[3], cub->parse.so);
	load_texture(cub, &cub->textures[4], "./Assets/sprites/zoom1.xpm");
	init_gun_textures(cub);
	init_door_textures(cub);
}
