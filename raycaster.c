

# include "Header/cub3d.h"



double angle_range(double ngl)
{
    if (ngl < 0)
        ngl += (2 * PI);
    if (ngl > (2 * PI))
        ngl -= (2 * PI);
    return (ngl);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(double angle, double *inter, double *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}
// int	wall_hit(float x, float y, t_cub *mlx)
// {
// 	int		x_m;
// 	int		y_m;

// 	if (x < 0 || y < 0)
// 		return (0);
// 	x_m = floor (x / TILE_SIZE); // get the x position in the map
// 	y_m = floor (y / TILE_SIZE); // get the y position in the map
// 	if ((y_m >= mlx->map.map_h || x_m >= mlx->map.map_w))
// 		return (0);
// 	if (mlx->map.map2d[y_m] && x_m <= (int)strlen(mlx->map.map2d[y_m]))
// 		if (mlx->map.map2d[y_m][x_m] == '1')
// 			return (0);
// 	return (1);
// }

int wall_hit(float x, float y, t_cub *mlx) {
    int x_m;
    int y_m;

    if (x < 0 || y < 0)
        return 0;

    x_m = floor(x / TILE_SIZE); // get the x position in the map
    y_m = floor(y / TILE_SIZE); // get the y position in the map

    // Check if the indices are within bounds of the map
    if (y_m < 0 || y_m >= mlx->map.map_h || x_m < 0 || x_m >= mlx->map.map_w)
        return 0;

    // Check if the map2d array is properly initialized
    if (mlx->map.map2d[y_m] && x_m < (int)strlen(mlx->map.map2d[y_m])) {
        if (mlx->map.map2d[y_m][x_m] == '1') {
            return 0; // There's a wall
        }
    }
    return 1; // No wall hit
}

// double get_hinter(t_cub *cub, double ngl)
// {
//     double hx;
//     double hy;
//     double y_step;
//     double x_step;
//     int pxl;

//     y_step = TILE_SIZE;
//     x_step = y_step / tan(ngl);
//     hy = floor((cub->plyr.plyr_y / TILE_SIZE) * TILE_SIZE);
//     pxl = inter_check(ngl, &hy, &y_step, 1);
//     hx = floor(cub->plyr.plyr_x + (hy - cub->plyr.plyr_y / tan(ngl)));
//     if ((unit_circle(ngl, 'y') && x_step > 0) || (!unit_circle(ngl, 'y') && x_step < 0))
// 		x_step *= -1;
//     while (wall_hit(hx, hy - pxl, cub))
// 	{
// 		hx += x_step;
// 		hy += y_step;
// 	}
//     return (sqrt(pow(hx - cub->plyr.plyr_x, 2) + pow(hy - cub->plyr.plyr_y, 2)));
// }

double get_hinter(t_cub *cub, double ngl)
{
    double hx;
    double hy;
    double y_step;
    double x_step;
    int pxl;

    // Check if the ray is facing up or down
    y_step = TILE_SIZE;
    if (ngl > 0 && ngl < PI) // Facing down
        y_step = TILE_SIZE;
    else // Facing up
        y_step = -TILE_SIZE;

    // Calculate x_step based on the angle
    x_step = y_step / tan(ngl);

    // Calculate the initial horizontal intersection
    hy = floor(cub->plyr.plyr_y / TILE_SIZE) * TILE_SIZE;
    if (ngl > 0 && ngl < PI) // If the ray is facing down
        hy += TILE_SIZE; // Move to the next tile boundary down

    pxl = (ngl > 0 && ngl < PI) ? 0 : -1; // Adjust for checking walls

    // Calculate the x-coordinate of the intersection based on the player's position and the angle
    hx = cub->plyr.plyr_x + (hy - cub->plyr.plyr_y) / tan(ngl);

    // Make sure x_step is negative when moving left, positive when moving right
    if ((ngl > PI / 2 && ngl < 3 * PI / 2) && x_step > 0) // Ray facing left
        x_step *= -1;
    if ((ngl < PI / 2 || ngl > 3 * PI / 2) && x_step < 0) // Ray facing right
        x_step *= -1;

    // Loop through intersections until a wall is hit
    while (wall_hit(hx, hy + pxl, cub)) {
        hx += x_step;
        hy += y_step;
    }

    // Return the distance to the intersection
    return sqrt(pow(hx - cub->plyr.plyr_x, 2) + pow(hy - cub->plyr.plyr_y, 2));
}


double	get_vinter(t_cub *cub, double angl)
{
	double	vx;
	double	vy;
	double	x_step;
	double	y_step;
	int		pxl;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	vx = floor(cub->plyr.plyr_x / TILE_SIZE) * TILE_SIZE;
	pxl = inter_check(angl, &vx, &x_step, 0);
	vy = cub->plyr.plyr_y + (vx - cub->plyr.plyr_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(vx - pxl, vy, cub))
	{
		vx += x_step;
		vy += y_step;
	}
	return (sqrt(pow(vx - cub->plyr.plyr_x, 2) + pow(vy - cub->plyr.plyr_y, 2))); // get the distance
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
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, 0xFFFF00);// 0xFFFFE0
        }
        i++;
    }
}

void raycaster(t_cub *cub)
{
    double h_inter;
    double v_inter;
    int nray;

    nray = 0;
    cub->ray.ray_ngl = angle_range(cub->plyr.angle - (cub->plyr.fov_rd / 2));
    printf("\t----ray-ngl--> %f\n",cub->ray.ray_ngl);
    while (nray < 100)
    {
        cub->ray.hit = 0;
        h_inter = get_hinter(cub, angle_range(cub->ray.ray_ngl));
        v_inter = get_vinter(cub, angle_range(cub->ray.ray_ngl));
        if (v_inter <= h_inter) // check the distance
			cub->ray.distance = v_inter; // get the distance
		else
		{
			cub->ray.distance = h_inter; // get the distance
			cub->ray.hit = 1; // flag for the wall
		}
        put_rays(cub, cub->ray.distance, cub->plyr.plyr_x, cub->plyr.plyr_y, cub->ray.ray_ngl);
        // render_wall(cub, ray); // render the wall
        nray++; // next ray
		// cub->ray.ray_ngl += (cub->plyr.fov_rd / cub->map.map_w);
        // cub->ray.ray_ngl += 0.01;
        cub->ray.ray_ngl = angle_range( cub->ray.ray_ngl + 0.01);
    }
}