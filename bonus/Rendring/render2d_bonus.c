/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/05 11:52:12 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	render_square(t_cub *cub, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < TILE_SIZE / 2)
	{
		x = 0;
		while (x < TILE_SIZE / 2)
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

void render_topv(t_cub *cub)
{
	cub->topv.range = PLAYER_RANGE / TILE_SIZE;
	int start_x;
	int end_x;
	int start_y;
	int end_y;
	start_x = cub->plyr.plyr_x/ TILE_SIZE  - cub->topv.range;
	if (start_x < 0)
		start_x = 0;
	end_x = cub->plyr.plyr_x/ TILE_SIZE + cub->topv.range;
	if (end_x >= cub->map.map_w)
		end_x = cub->map.map_w;
	// printf("topv->range == %d\n", cub->topv.range);
	printf("start_x == %d , end_x = %d\n", start_x, end_x);
	// printf("p_x == %d , p_y = %d\n", cub->plyr.plyr_x, cub->plyr.plyr_y);
	start_y = cub->plyr.plyr_y/ TILE_SIZE - cub->topv.range;
	if (start_y < 0)
		start_y = 0;
	end_y = cub->plyr.plyr_y/ TILE_SIZE + cub->topv.range;
	if (end_y >= cub->map.map_h)
		end_y = cub->map.map_h;
	int y, x;
	int dist;

	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		while (x <= end_x)
		{
		// printf("hello\n");
			dist = abs(cub->plyr.plyr_x/ TILE_SIZE - x) + abs(cub->plyr.plyr_y/ TILE_SIZE  - y);
				printf("hello %d\n", dist);
			if (dist * TILE_SIZE <= PLAYER_RANGE)
			{
				printf("\tHERE\n");
				if (cub->map.map2d[y][x] == '1')
					render_square(cub, 0x000000);
				else if (cub->map.map2d[y][x] == '0' || cub->map.map2d[y][x] == 'P')
					render_square(cub, 0xffffff);
				else if (cub->map.map2d[y][x] == 'D')
				render_square(cub, 0x00FF00);
			}
			x++;
		}
		y++;
	}
	render_circle(cub, 0xFF0000);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}
