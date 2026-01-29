/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:47:30 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/26 17:42:31 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

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
