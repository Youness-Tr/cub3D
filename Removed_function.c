/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Removed_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:51:24 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 10:51:45 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

/****** Remove Me Later **********/
void find_plyr_cordn(t_cub *o)
{
	int i;
	int j;

	i = 0;
	while (i < o->map.map_h)
	{
		j = 0;
		while (j < o->map.map_w)
		{
			if (o->map.map2d[i][j] == 'N')
			{
				o->map.posx = j;
				o->map.posy = i;
				break;
			}
			j++;
		}
		i++;
	}
}
/****** Remove Me Later ^ **********/