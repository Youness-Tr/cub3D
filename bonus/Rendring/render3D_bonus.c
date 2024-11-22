/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:33:58 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/22 19:08:41 by kali             ###   ########.fr       */
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


t_img *get_door_frame(t_cub *cub)
{
	int i;

	i = 0;
	while (i < cub->ndoors)
	{
		if (cub->doors[i].open)
			return (&cub->textures[cub->doors[i].frame]);
		i++;
	}
	return (&cub->textures[4]);
}
t_img	*get_texture(t_cub *cub, int flag) // get the color of the wall
{
	cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl); // normalize the angle
	if (cub->ray.hit_door == 1)
		return (get_door_frame(cub));
	if (cub->ray.hit_door == 2)
		return (&cub->textures[6]);
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
			if (cub->ray.hit_door == 2)
			{
				if ((unsigned int)color  != 0xFF000000) // Check if the pixel is not fully transparent
					 my_mlx_pixel_put(&cub->img, x, y, color);
			}
			else
            	my_mlx_pixel_put(&cub->img, x, y, color);
		y++;
	}
}

// void render_door(t_cub *cub, int x, int y, double offset);

void render_three_d(t_cub *cub, double distnce, int raypt, int tex_x)
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
	// render_door(cub, cub->door.x, cub->door.y, cub->door.offset);
}
