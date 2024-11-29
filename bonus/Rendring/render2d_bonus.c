/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/29 11:22:54 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	render_square(t_cub *cub, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub->topv.factor)
	{
		x = 0;
		while (x < cub->topv.factor)
		{
			my_mlx_pixel_put(&cub->img, ((cub->topv.i * TILE_SIZE) * MINI_MAP)
				+ x, ((cub->topv.j * TILE_SIZE) * MINI_MAP + y), color);
			x++;
		}
		y++;
	}
}

void	render_circle(t_cub *cub, int color)
{
	int	x;
	int	y;
	int	radius;

	radius = PLAYER_RADIUS * MINI_MAP;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				my_mlx_pixel_put(&cub->img, cub->plyr.plyr_x * MINI_MAP + x,
					cub->plyr.plyr_y * MINI_MAP + y, color);
			}
			x++;
		}
		y++;
	}
}

void	render_mini_2d(t_cub *cub)
{
	cub->topv.j = 0;
	cub->map.map2d[cub->parse.player_x][cub->parse.player_y] = 'P';
	cub->topv.factor = (float)(cub->var.s_w * MINI_MAP) / cub->map.map_w + 1;
	while (cub->topv.j < cub->map.map_h + 1)
	{
		cub->topv.i = 0;
		while (cub->topv.i < cub->map.map_w + 1)
		{
			if (cub->map.map2d[cub->topv.j][cub->topv.i] == '1')
				render_square(cub, 0x000000);
			else if (cub->map.map2d[cub->topv.j][cub->topv.i] == '0'
				|| cub->map.map2d[cub->topv.j][cub->topv.i] == 'P')
			{
				render_square(cub, 0xffffff);
			}
			else if (cub->map.map2d[cub->topv.j][cub->topv.i] == 'D')
			{
				render_square(cub, 0x00FF00);
			}
			cub->topv.i++;
		}
		cub->topv.j++;
	}
	render_circle(cub, 0xFF0000);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}
