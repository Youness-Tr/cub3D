/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:33:58 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/15 11:59:52 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

// int get_color(t_cub *cub, int flag) // get the color of the wall
// {
// 	cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl); // normalize the angle
// 	if (flag == 0)
// 	{
// 		if (cub->ray.ray_ngl > PI / 2 && cub->ray.ray_ngl < 3 * (PI / 2))
// 			return (0xA5D6A7); // west wall
// 		else
// 			return (0x81C784); // east wall
// 	}
// 	else
// 	{
// 		if (cub->ray.ray_ngl > 0 && cub->ray.ray_ngl < PI)
// 			return (0x388E3C); // south wall
// 		else
// 			return (0x4CAF50); // north wall
// 	}
// }
// void render_wll(t_cub *cub, int toppxl, int lowpxl, int raypt)
// {
//     int color;

//     color = get_color(cub, cub->ray.hit);
//     while (lowpxl > toppxl)
//         my_mlx_pixel_put(&cub->img, raypt, toppxl++, color);
// }

t_img	*get_texture(t_cub *cub, int flag) // get the color of the wall
{
	cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (cub->ray.ray_ngl > PI / 2 && cub->ray.ray_ngl < 3 * (PI / 2))
			return (&cub->textures[0]); // west wall
		else
			return (&cub->textures[1]); // east wall
	}
	else
	{
		if (cub->ray.ray_ngl > 0 && cub->ray.ray_ngl < PI)
			return (&cub->textures[2]); // south wall
		else
			return (&cub->textures[3]); // north wall
	}
}

void	render_textured_wall(t_cub *cub, int x, int wall_height, int wall_top,
		int wall_bottom, int tex_x)
{
	int		tex_y;
	int		color;
	int		y;
	t_img	*texture;

	(void)wall_height;
	texture = get_texture(cub, cub->ray.hit);
	y = wall_top;
	while (y < wall_bottom)
	{
		tex_y = ((y - wall_top) * texture->h) / (wall_bottom - wall_top);
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
	int		toppxl;
	int		lowpxl;
	double	dstnceplane;

	s_w = WIN_W;
	s_h = WIN_H;
	// Correct the distance for the fish-eye effect
	distnce *= cos(cub->ray.ray_ngl - cub->plyr.angle);
	dstnceplane = (s_w / 2) / tan(cub->plyr.fov_rd / 2);
	wll_h = (TILE_SIZE / distnce) * dstnceplane;
	toppxl = (s_h / 2) - (wll_h / 2);
	lowpxl = (s_h / 2) + (wll_h / 2);
	// Ensure the top and bottom pixel positions are within screen bounds
	// if (toppxl > s_h) // I think hnaya khass  ikom / s_h
	//     toppxl = s_h;
	// if (lowpxl < 0)
	//     lowpxl = 0;
	render_textured_wall(cub, raypt, wll_h, toppxl, lowpxl, tex_x);
	draw_floor_ceiling(cub, raypt, toppxl, lowpxl);
}
