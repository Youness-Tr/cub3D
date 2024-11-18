/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:47:30 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/18 10:38:31 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

// void put_line(t_cub *cub, int len, int x, int y)
// {
//     float deltaX;
//     float deltaY;

//     int i = 0;
//     deltaX = cos(cub->plyr.angle);
//     deltaY = sin(cub->plyr.angle);

//     while (i < len)
//     {
//         int draw_x = x + i * deltaX;
//         int draw_y = y + i * deltaY;

//         if (draw_x >= 0 && draw_x < TILE_SIZE * cub->map.map_w &&
//             draw_y >= 0 && draw_y < TILE_SIZE * cub->map.map_h)
//         {
//             mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, 0x000000);
//         }
//         i++;
//     }
// }

// void put_rays(t_cub *cub, int len, int x, int y, float ngl)
// {
//     float deltaX;
//     float deltaY;

//     int i = 0;
//     deltaX = cos(ngl);
//     deltaY = sin(ngl);

//     while (i < len)
//     {
//         int draw_x = x + i * deltaX;
//         int draw_y = y + i * deltaY;

//         // Draw only if within window bounds
//         if (draw_x >= 0 && draw_x < TILE_SIZE * cub->map.map_w &&
//             draw_y >= 0 && draw_y < TILE_SIZE * cub->map.map_h)
//         {
//             mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y,
// 0xFFFF00);0xFFFFE0
//         }
//         i++;
//     }
// }
// int s_w, s_h;
// s_w = data->gme->var.s_w;
// s_h = data->gme->var.s_w;
// if (x < 0 || x > s_w)
//     return ;
// if (y > s_h || s_h < 0)
//     return ;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= data->gme->var.s_w || y < 0 || y >= data->gme->var.s_h)
		return ;
	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_floor_ceiling(t_cub *cub, int raypt, int toppxl, int lowpxl)
{
	int	i;

	i = lowpxl;
	while (i < cub->var.s_h)
		my_mlx_pixel_put(&cub->img, raypt, i++, cub->parse.f);
	i = 0;
	while (i < toppxl)
		my_mlx_pixel_put(&cub->img, raypt, i++, cub->parse.c);
}
