/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:33:58 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/03 19:04:53 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

t_img	*get_door_frame(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < cub->ndoors)
	{
		if (cub->doors[i].open && cub->doors[i].distance <= DOOR_OPEN_DISTANCE)
		{
			return (&cub->door[cub->doors[i].frame]);
		}
		i++;
	}
	if (cub->default_door.open == -1)
	{
		return (&cub->door[0]);
	}
	else
		return (&cub->door[cub->default_door.frame]);
}

t_img	*get_texture(t_cub *cub, int flag)
{
	cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl);
	if (cub->ray.hit_door == 1)
		return (get_door_frame(cub));
	if (flag == 0)
	{
		if (cub->ray.ray_ngl > PI / 2 && cub->ray.ray_ngl < 3 * (PI / 2))
			return (&cub->textures[0]);
		else
			return (&cub->textures[1]);
	}
	else
	{
		if (cub->ray.ray_ngl > 0 && cub->ray.ray_ngl < PI)
			return (&cub->textures[2]);
		else
			return (&cub->textures[3]);
	}
}

void	render_textured_wall(t_cub *cub, int x, int tex_x)
{
	int		tex_y;
	int		color;
	int		y;
	t_img	*texture;

	texture = get_texture(cub, cub->ray.hit);
	y = cub->var.toppxl;
	while (y < cub->var.lowpxl)
	{
		tex_y = ((y - cub->var.toppxl) * texture->h) / (cub->var.lowpxl
				- cub->var.toppxl);
		color = *(unsigned int *)(texture->addr + (tex_y * texture->len + tex_x
					* (texture->bpp / 8)));
		my_mlx_pixel_put(&cub->img, x, y, color);
		y++;
	}
}

void	render_three_d(t_cub *cub, double distnce, int raypt, int tex_x)
{
	int		s_w;
	int		s_h;
	double	wll_h;
	double	dstnceplane;

	s_w = WIN_W;
	s_h = WIN_H;
	distnce *= cos(cub->ray.ray_ngl - cub->plyr.angle);
	if (distnce < 1)
		distnce = 1;
	dstnceplane = (s_w / 2) / tan(cub->plyr.fov_rd / 2);
	wll_h = (TILE_SIZE / distnce) * dstnceplane;
	cub->var.toppxl = (s_h / 2) - (wll_h / 2);
	cub->var.lowpxl = (s_h / 2) + (wll_h / 2);
	if (cub->map.map2d[cub->plyr.plyr_y / TILE_SIZE][cub->plyr.plyr_x
		/ TILE_SIZE] != 'D')
	{
		render_textured_wall(cub, raypt, tex_x);
		draw_floor_ceiling(cub, raypt, cub->var.toppxl, cub->var.lowpxl);
	}
}
