/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:09:19 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/26 16:12:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

double	get_hinter(t_cub *cub, double ngl)
{
	cub->var.y_step = TILE_SIZE;
	if (ngl > 0 && ngl < PI)
		cub->var.y_step = TILE_SIZE;
	else
		cub->var.y_step = -TILE_SIZE;
	cub->var.x_step = cub->var.y_step / tan(ngl);
	cub->var.hy = floor(cub->plyr.plyr_y / TILE_SIZE) * TILE_SIZE;
	if (ngl > 0 && ngl < PI)
		cub->var.hy += TILE_SIZE;
	if (ngl > 0 && ngl < PI)
		cub->var.pxl = 0;
	else
		cub->var.pxl = -1;
	cub->var.hx = cub->plyr.plyr_x + (cub->var.hy - cub->plyr.plyr_y)
		/ tan(ngl);
	if ((ngl > PI / 2 && ngl < 3 * PI / 2) && cub->var.x_step > 0)
		cub->var.x_step *= -1;
	if ((ngl < PI / 2 || ngl > 3 * PI / 2) && cub->var.x_step < 0)
		cub->var.x_step *= -1;
	while (wall_hit(cub->var.hx, cub->var.hy + cub->var.pxl, cub))
	{
		cub->var.hx += cub->var.x_step;
		cub->var.hy += cub->var.y_step;
	}
	return (distance(cub, cub->var.hx, cub->var.hy));
}

double	get_vinter(t_cub *cub, double ngl)
{
	cub->var.x_step = TILE_SIZE;
	if (ngl > PI / 2 && ngl < 3 * PI / 2)
		cub->var.x_step = -TILE_SIZE;
	cub->var.y_step = cub->var.x_step * tan(ngl);
	cub->var.hx = floor(cub->plyr.plyr_x / TILE_SIZE) * TILE_SIZE;
	if (ngl < PI / 2 || ngl > 3 * PI / 2)
		cub->var.hx += TILE_SIZE;
	if (ngl < PI / 2 || ngl > 3 * PI / 2)
		cub->var.pxl = 0;
	else
		cub->var.pxl = -1;
	cub->var.hy = cub->plyr.plyr_y + (cub->var.hx - cub->plyr.plyr_x)
		* tan(ngl);
	if ((ngl > 0 && ngl < PI) && cub->var.y_step < 0)
		cub->var.y_step *= -1;
	if ((ngl > PI && ngl < 2 * PI) && cub->var.y_step > 0)
		cub->var.y_step *= -1;
	while (wall_hit(cub->var.hx + cub->var.pxl, cub->var.hy, cub))
	{
		cub->var.hx += cub->var.x_step;
		cub->var.hy += cub->var.y_step;
	}
	return (distance(cub, cub->var.hx, cub->var.hy));
}

void	set_distance(t_cub *cub)
{
	if (cub->var.v_inter <= cub->var.h_inter)
		cub->ray.distance = cub->var.v_inter;
	else
	{
		cub->ray.distance = cub->var.h_inter;
		cub->ray.hit = 1;
	}
}

void door_handling(t_cub *cub)
{
	int x;
	int y;

		x = (int)(cub->ray.hit_x / TILE_SIZE);
		y = (int)(cub->ray.hit_y / TILE_SIZE);
		if (cub->map.map2d[y][x] == 'D')
			cub->ray.hit_door = 1;
		else if (cub->map.map2d[y][x] == '0')
		{
			if (cub->map.map2d[y - 1][x] == 'D' && cub->ray.hit)
				cub->ray.hit_door = 1;
			else if (cub->map.map2d[y][x - 1] == 'D' && !cub->ray.hit)
				cub->ray.hit_door = 1;
			else if (cub->map.map2d[y + 1][x] == 'D' && cub->ray.hit)
				cub->ray.hit_door = 1;
			else if (cub->map.map2d[y][x + 1] == 'D' && !cub->ray.hit)
				cub->ray.hit_door = 1;
			else
				cub->ray.hit_door = 0;
		}
		else
			cub->ray.hit_door = 0;
}

int raycaster(t_cub *cub)
{
	cub->var.nray = 0;
	cub->ray.ray_ngl = angle_range(cub->plyr.angle - (cub->plyr.fov_rd / 2));
	cub->var.ngl = (cub->plyr.fov_rd / ((double)cub->var.s_w));
	while (cub->var.nray < cub->var.s_w)
	{
		cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl);
		cub->ray.hit = 0;
		cub->ray.hit_door = 0;
		cub->var.h_inter = get_hinter(cub, angle_range(cub->ray.ray_ngl));
		cub->var.v_inter = get_vinter(cub, angle_range(cub->ray.ray_ngl));
		set_distance(cub);
		cub->ray.hit_x = cub->plyr.plyr_x + cub->ray.distance * cos(angle_range(cub->ray.ray_ngl));
		cub->ray.hit_y = cub->plyr.plyr_y + cub->ray.distance * sin(angle_range(cub->ray.ray_ngl));
		door_handling(cub);
		cub->var.wall_x = calculate_wall_x(&cub->ray);
		cub->var.tex_x = get_texture_x(cub, cub->var.wall_x);
		render_three_d(cub, cub->ray.distance, cub->var.nray, cub->var.tex_x);
		cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl + cub->var.ngl);
		// put_rays(cub, cub->ray.distance * MINI_MAP, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP, cub->ray.ray_ngl);
		cub->var.nray++;
	}
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
	return (0);
}
