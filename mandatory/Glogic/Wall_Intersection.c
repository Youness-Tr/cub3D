/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_Intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:43:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/18 10:40:08 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

int	is_wall(t_cub *cub, double x, double y)
{
	int		px;
	int		py;
	double	dx;
	double	dy;
	double	step;

	step = 5.0;
	dx = -step;
	while (dx <= step)
	{
		dy = -step;
		while (dy <= step)
		{
			px = floor((x + dx) / TILE_SIZE);
			py = floor((y + dy) / TILE_SIZE);
			if (px >= cub->map.map_w || px < 0 || py < 0
				|| py >= cub->map.map_h)
				return (0);
			if (cub->map.map2d[py][px] == '1')
				return (0);
			dy += step;
		}
		dx += step;
	}
	return (1);
}
