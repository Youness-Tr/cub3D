/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:09:19 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/18 18:47:03 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

double	distance(t_cub *cub, double x, double y)
{
	return (sqrt(pow(x - cub->plyr.plyr_x, 2) + pow(y - cub->plyr.plyr_y, 2)));
}

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

void put_rays(t_cub *cub, int len, int x, int y, float ngl)
{
    float deltaX;
    float deltaY;

    int i = 0;
    deltaX = cos(ngl);
    deltaY = sin(ngl);

    while (i < len)
    {
        int draw_x = x + i * deltaX;
        int draw_y = y + i * deltaY;

        // Draw only if within window bounds
        if (draw_x >= 0 && draw_x < TILE_SIZE * cub->map.map_w &&
            draw_y >= 0 && draw_y < TILE_SIZE * cub->map.map_h)
        {
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y,0xFF0000);
        }
        i++;
    }
}

// void set_ray_vars(t_cub *cub)
// {

// }
// int get_door(t_cub *cub)
// {
// 	if (distance < 1.0)
// 		cub->door.open = 1;
// 	else
// 		cub->door.open = 0;
// 	return (cub->door.open);
// }

// void render_weapon(t_cub *cub);
int raycaster(t_cub *cub)
{
	cub->var.nray = 0;
	cub->ray.ray_ngl = angle_range(cub->plyr.angle - (cub->plyr.fov_rd / 2));
	cub->var.ngl = (cub->plyr.fov_rd / ((double)cub->var.s_w));
	while (cub->var.nray < cub->var.s_w)
	{
		cub->ray.hit = 0;
		cub->ray.hit_door = 0;
		cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl);
		cub->var.h_inter = get_hinter(cub, angle_range(cub->ray.ray_ngl));
		cub->var.v_inter = get_vinter(cub, angle_range(cub->ray.ray_ngl));
		set_distance(cub);
		cub->ray.hit_x = cub->plyr.plyr_x + cub->ray.distance * cos(angle_range(cub->ray.ray_ngl));
		cub->ray.hit_y = cub->plyr.plyr_y + cub->ray.distance * sin(angle_range(cub->ray.ray_ngl));
		int map_x = (int)(cub->ray.hit_x / TILE_SIZE);
        int map_y = (int)(cub->ray.hit_y / TILE_SIZE);
		// printf("map_x = %d, map_y = %d | `%c'\n", map_x, map_y, cub->map.map2d[map_y][map_x]);
         if (cub->map.map2d[map_y][map_x] == 'D' || cub->map.map2d[map_y][map_x] == 'E')
            cub->ray.hit_door = 1;
        else if (cub->map.map2d[map_y][map_x] == '0' && !cub->door.open)
        {
            if ((map_x > 0 && cub->map.map2d[map_y][map_x - 1] == 'D') ||
                (map_x < cub->map.map_w - 1 && cub->map.map2d[map_y][map_x + 1] == 'D') ||
                (map_y > 0 && cub->map.map2d[map_y - 1][map_x] == 'D') ||
                (map_y < cub->map.map_h - 1 && cub->map.map2d[map_y + 1][map_x] == 'D'))
            {
				// cub->map.map2d[map_y][map_x] = 'D';
                cub->ray.hit_door = 1;
				cub->door.frame = 9;
            }
        }
		 if (cub->ray.hit_door)
        {
            if (cub->door.open)
            {
                cub->map.map2d[map_y][map_x] = 'E'; // Open door texture
            }
            else
            {
                cub->map.map2d[map_y][map_x] = 'D'; // Closed door texture
            }
        }
		cub->var.wall_x = calculate_wall_x(&cub->ray);
		cub->var.tex_x = get_texture_x(cub, cub->var.wall_x);
		render_three_d(cub, cub->ray.distance, cub->var.nray, cub->var.tex_x);
		cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl + cub->var.ngl);
		cub->var.nray++;
	}
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
	return (0);
}

// put_rays(cub,cub->ray.distance  * MINI_MAP, cub->plyr.plyr_x * MINI_MAP,
// cub->plyr.plyr_y * MINI_MAP, cub->ray.ray_ngl);
// put_line(cub, 30, (int)cub->plyr.plyr_x * MINI_MAP, (int)cub->plyr.plyr_y
// * MINI_MAP);