/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:33:58 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 11:12:32 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"



void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
    // int s_w, s_h;
    // s_w = data->gme->var.s_w;
    // s_h = data->gme->var.s_w;
    // if (x < 0 || x > s_w)
    //     return;
    // if (y > s_h || s_h < 0)
    //     return;
     if (x < 0 || x >= data->gme->var.s_w || y < 0 || y >= data->gme->var.s_h)
        return;
    dst = data->addr + (y * data->len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}


void draw_floor_ceiling(t_cub *cub, int raypt, int toppxl, int lowpxl) // draw the floor and the ceiling
{
 int  i;
//  int  c;

	i = lowpxl;
	while (i < cub->var.s_h)
		my_mlx_pixel_put(&cub->img, raypt, i++, 0xC19A6B); // floor C8E6C9
	i = 0;
	while (i < toppxl)
		my_mlx_pixel_put(&cub->img, raypt, i++, 0xF0EAD6); // ceiling //F0EAD6
}


int get_color(t_cub *cub, int flag) // get the color of the wall
{
	cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (cub->ray.ray_ngl > PI / 2 && cub->ray.ray_ngl < 3 * (PI / 2))
			return (0xA5D6A7); // west wall
		else
			return (0x81C784); // east wall
	}
	else
	{
		if (cub->ray.ray_ngl > 0 && cub->ray.ray_ngl < PI)
			return (0x388E3C); // south wall
		else
			return (0x4CAF50); // north wall
	}
}

void render_wll(t_cub *cub, int toppxl, int lowpxl, int raypt)
{

    printf(MAGENTA "lowpxl |%d| *** toppxl |%d|\n", lowpxl, toppxl);
    int color;

    color = get_color(cub, cub->ray.hit);
    while (lowpxl > toppxl)
        my_mlx_pixel_put(&cub->img, raypt, toppxl++, color);
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}

void ft_renderThreeD(t_cub *cub, double distnce, int raypt)
{

    int s_w;
    int s_h;
    double wll_h;
    int toppxl;
    int lowpxl;
    // void *tmp_img;

    s_w = cub->var.s_w;
    s_h = cub->var.s_h;
    printf(WHITE"\t\t\t\t\t %f\n", distnce);
    distnce *= cos(cub->ray.ray_ngl - cub->plyr.angle);
    printf(RED "--------------------------->>(S_W : %d)\n\t(S_H : %d)\n" RES, s_w, s_h);
    wll_h = (TILE_SIZE / distnce) * ((s_w / 2) * tan(cub->plyr.fov_rd / 2));
    printf(CYAN"\t\t\t\tWall_H |----->> %f\n", wll_h);
    toppxl = (s_h / 2) - (wll_h / 2);
    lowpxl = (s_h / 2) + (wll_h / 2);
    if (toppxl > s_w)
        toppxl = s_w;
    if (lowpxl < 0)
        lowpxl = 0;
    render_wll(cub, toppxl, lowpxl, raypt);
    draw_floor_ceiling(cub, raypt, toppxl, lowpxl);
}
