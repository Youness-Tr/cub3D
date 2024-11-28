/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:44:17 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/28 10:44:20 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	get_doors_cordn(t_cub *o)
{
	int	i;
	int	j;
	int	k;

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

void	ndoors(t_cub *o)
{
	int	i;
	int	j;

	i = 0;
	while (i < o->map.map_h)
	{
		j = 0;
		while (j < o->map.map_w)
		{
			if (o->map.map2d[i][j] == 'D')
				o->ndoors++;
			j++;
		}
		i++;
	}
}
