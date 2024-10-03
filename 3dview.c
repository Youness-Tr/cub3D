# include "Header/cub3d.h"

void	my_mlx_pixel_put2(t_cub *cub, int x, int y, int color)	// put the pixel
{
    int sw, sh;

    sw = cub->map.map_w * TILE_SIZE;
    sh = cub->map.map_h * TILE_SIZE;
	if (x < 0) // check the x position
		return ;
	else if (x >= sw)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= sh)
		return ;
	// mlx_put_pixel(cub->img, x, y, color); // put the pixel
    mlx_pixel_put(cub->mlxp, cub->mlx_w, x , y, color);

}

float	nor_angle(float angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

void	draw_floor_ceiling(t_cub *cub, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;
	int		c;
    int sw;

    sw = cub->map.map_w * TILE_SIZE;
	i = b_pix;
	while (i < sw)
		my_mlx_pixel_put2(cub, ray, i++, 0xB99470FF); // floor
	i = 0;
	while (i < t_pix)
		my_mlx_pixel_put2(cub, ray, i++, 0x89CFF3FF); // ceiling
}

int	get_color(t_cub *cub, int flag)	// get the color of the wall
{
	cub->ray.ray_ngl = nor_angle(cub->ray.ray_ngl); // normalize the angle
	if (flag == 0)
	{
		if (cub->ray.ray_ngl > PI / 2 && cub->ray.ray_ngl < 3 * (PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (cub->ray.ray_ngl > 0 && cub->ray.ray_ngl < PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_wall(t_cub *cub, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = get_color(cub, cub->ray.hit);
	while (t_pix < b_pix)
		my_mlx_pixel_put2(cub, ray, t_pix++, color);
}

void	render_wall(t_cub *cub, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;
    int sw, sh;

    sw = cub->map.map_w * TILE_SIZE ;
    sh = cub->map.map_h * TILE_SIZE;
    cub->ray.distance *= cos(nor_angle(cub->ray.ray_ngl - cub->plyr.angle));             // fix the fisheye
    wall_h = (TILE_SIZE / cub->ray.distance) * ((sw/ 2) / tan(cub->plyr.fov_rd / 2)); // get the wall height
	b_pix = (sh / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (sh / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > sh) // check the bottom pixel
		b_pix = sh;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(cub, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(cub, ray, t_pix, b_pix); // draw the floor and the ceiling
}
