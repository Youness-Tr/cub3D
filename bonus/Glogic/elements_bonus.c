/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:53:20 by youness           #+#    #+#             */
/*   Updated: 2024/12/05 10:40:42 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	shoot(t_cub *cub)
{
	if (cub->is_shooting)
	{
		
		usleep(40000);// !need to find an other way
		cub->gun_frame++;
		if (cub->gun_frame >= MAX_GUN)
			cub->gun_frame = 0;
	}
	if (!cub->is_shooting && cub->gun_frame != 0)
	{
		usleep(40000);// !need to find an other way
		cub->gun_frame--;
	}
}

void	render_weapon(t_cub *cub)
{
	int				weapon_x;
	int				weapon_y;
	unsigned int	color;

	weapon_x = (cub->var.s_w - (cub->gun[cub->gun_frame].w)) / 2;
	weapon_y = cub->var.s_h - cub->gun[cub->gun_frame].h;
	cub->var.y = 0;
	while (cub->var.y < cub->gun[cub->gun_frame].h)
	{
		cub->var.x = 0;
		while (cub->var.x < cub->gun[cub->gun_frame].w)
		{
			color = *(unsigned int *)(cub->gun[cub->gun_frame].addr
					+ (cub->var.y * cub->gun[cub->gun_frame].len + cub->var.x
						* (cub->gun[cub->gun_frame].bpp / 8)));
			if (color != 0xFF000000)
			{
				my_mlx_pixel_put(&cub->img, weapon_x + cub->var.x, weapon_y
					+ cub->var.y, color);
			}
			cub->var.x++;
		}
		cub->var.y++;
	}
}

void	count_door_distances(t_cub *cub)
{
	double	player_x;
	double	player_y;

	player_x = cub->plyr.plyr_x / TILE_SIZE;
	player_y = cub->plyr.plyr_y / TILE_SIZE;
	cub->var.x = 0;
	while (cub->var.x < cub->ndoors)
	{
		cub->doors[cub->var.x].distance = sqrt(pow(player_x
					- cub->doors[cub->var.x].x / TILE_SIZE, 2) + pow(player_y
					- cub->doors[cub->var.x].y / TILE_SIZE, 2));
		cub->var.x++;
	}
}

void	handle_door_interaction(t_cub *cub, int i)
{
	while (i < cub->ndoors)
	{
		count_door_distances(cub);
		if (cub->doors[i].distance <= DOOR_OPEN_DISTANCE)
		{
			cub->doors[i].open = 1;
			cub->default_door.open = 0;
			cub->default_door.frame = MAX_DOOR;
			cub->doors[i].frame++;
			if (cub->doors[i].frame > MAX_DOOR)
				cub->doors[i].frame = MAX_DOOR;
		}
		else
		{
			cub->doors[i].open = 0;
			cub->doors[i].frame--;
			cub->default_door.frame--;
			if (cub->default_door.frame < 0)
				cub->default_door.frame = 0;
			if (cub->doors[i].frame < 0)
				cub->doors[i].frame = 0;
		}
		i++;
	}
}

void	set_gun(t_cub *cub, char *file)
{
	cub->textures[4].img = mlx_xpm_file_to_image(cub->mlxp, file,
			&cub->textures[4].w, &cub->textures[4].h);
	if (!cub->textures[4].img)
	{
		ft_errorv2(&cub->parse, "Error: Could not load texture");
		_close_window(cub);
	}
}
