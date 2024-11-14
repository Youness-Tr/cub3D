/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:57:28 by kali              #+#    #+#             */
/*   Updated: 2024/11/01 18:48:03 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"
//!remove unused vars
void	init_map(t_cub *cub, char *file)
{
	(void)file;
	cub->map.map2d = cub->parse.map;
	if (!cub->map.map2d)
	{
		ft_error("Error: Could not load map");
		exit(1);//!free memory here
	}
	cub->map.map_h = cub->parse.lines;
	cub->map.map_w = cub->parse.map_len;
	cub->map.posx = cub->parse.player_Y;
	cub->map.posy = cub->parse.player_x;
}

void	player_ngl(t_cub *cub)
{
	int	x;
	int	y;

	x = cub->parse.player_x;
	y = cub->parse.player_Y;
	if (cub->parse.map[y][x] == 'E')
		cub->plyr.angle = (90 * PI) / 180;
	else if (cub->parse.map[y][x] == 'N')
		cub->plyr.angle = (3 * PI) / 2;
	else if (cub->parse.map[y][x] == 'W')
		cub->plyr.angle = PI;
	else if (cub->parse.map[y][x] == 'S')
		cub->plyr.angle = 0;
	cub->map.map2d[y][x] = 'P';
	cub->plyr.angle = angle_range(cub->plyr.angle);
}

void	init_plyr(t_cub *cub)
{
	cub->plyr.plyr_x = cub->map.posx * TILE_SIZE + TILE_SIZE / 2;
	cub->plyr.plyr_y = cub->map.posy * TILE_SIZE + TILE_SIZE / 2;
	cub->plyr.fov_rd = FOV;
	player_ngl(cub);
	cub->move_forward = 0;
	cub->move_backward = 0;
	cub->move_left = 0;
	cub->move_right = 0;
	cub->rotate_left = 0;
	cub->rotate_right = 0;
	cub->plyr.rot = ROT_SPEED;
}