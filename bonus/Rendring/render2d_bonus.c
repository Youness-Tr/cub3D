/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/20 09:56:09 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

/*******just for debuging ********************/

void	render_square(t_img *img, int x_start, int y_start, int size, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			my_mlx_pixel_put(img, x_start + x, y_start + y, color);
			x++;
		}
		y++;
	}
}


/*******just for debuging ********************/

// void	render_2d(t_cub *cub)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	mlx_clear_window(cub->mlxp, cub->mlx_w);
// 	while (j < cub->map.map_h)
// 	{
// 		i = 0;
// 		while (i < cub->map.map_w)
// 		{
// 			if (cub->map.map2d[j][i] == '1')
// 				render_square(&cub->img, i * TILE_SIZE, j * TILE_SIZE,
// 					TILE_SIZE, 0xC0C0C0);
// 			else if (cub->map.map2d[j][i] == '0' || cub->map.map2d[j][i] == 'N')
// 			{
// 				render_square(&cub->img, i * TILE_SIZE, j * TILE_SIZE,
// 					TILE_SIZE, 0x654321); // 0x8B5A2B
// 			}
// 			i++;
// 		}
// 		j++;
// 	}
// 	// render_square(&cub->img, cub->plyr.plyr_x , cub->plyr.plyr_y,
// 		PLAYER_RADIUS,0xFFFFFF);
// 	render_circle(&cub->img, cub->plyr.plyr_x, cub->plyr.plyr_y, PLAYER_RADIUS,
// 		0x000000);
// 	mlx_clear_window(cub->mlxp, cub->mlx_w);
// 	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
// }

void	render_circle(t_img *img, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			// Check if the point (cx + x, cy + y) is inside the circle
			if (x * x + y * y <= radius * radius)
			{
				my_mlx_pixel_put(img, cx + x, cy + y, color);
			}
			x++;
		}
		y++;
	}
}

void	render_mini_2d(t_cub *cub)
{
	int i;
	int j;
	int len;

	j = 0;
	len = 0;
	// while (cub->map.map2d[0][len] && cub->map.map2d[0][len] !=' ')
	// 	len++;
	cub->map.map2d[cub->parse.player_x][cub->parse.player_y] = 'P';
	int factor = (float)(cub->var.s_w * MINI_MAP) / cub->map.map_w +1;
	while (j < cub->map.map_h + 1)
	{
		i = 0;
		while (i < cub->map.map_w + 1)
		{
			if (cub->map.map2d[j][i] == '1')
				render_square(&cub->img, (i * TILE_SIZE) * MINI_MAP, (j* TILE_SIZE) * MINI_MAP, factor,
					0x000000);
			else if (cub->map.map2d[j][i] == '0' || cub->map.map2d[j][i] == 'P')
			{
				render_square(&cub->img, (i * TILE_SIZE) * MINI_MAP, (j
						* TILE_SIZE) * MINI_MAP, factor,
					0xffffff); // 0x8B5A2B
			}
			else if (cub->map.map2d[j][i] == 'D')
			{
				render_square(&cub->img, (i * TILE_SIZE) * MINI_MAP, (j
						* TILE_SIZE) * MINI_MAP, factor,
					0x00FF00); // 0x8B5A2B
			}
			i++;
		}
		j++;
	}
	render_circle(&cub->img, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP, PLAYER_RADIUS * MINI_MAP, 0xFF0000);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}
