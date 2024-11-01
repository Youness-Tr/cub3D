/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:09:19 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/01 18:52:32 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

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
//
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
//
int wall_hit(float x, float y, t_cub *mlx) {
    int x_m;
    int y_m;
//
    if (x < 0 || y < 0)
        return 0;
//
    x_m = floor(x / TILE_SIZE); // get the x position in the map
    y_m = floor(y / TILE_SIZE); // get the y position in the map
//
    // Check if the indices are within bounds of the map
    if (y_m < 0 || y_m >= mlx->map.map_h || x_m < 0 || x_m >= mlx->map.map_w)
        return 0;
//
    // Check if the map2d array is properly initialized
    if (mlx->map.map2d[y_m] && x_m < (int)strlen(mlx->map.map2d[y_m])) {
        if (mlx->map.map2d[y_m][x_m] == '1') {
            return 0; // There's a wall
        }
    }
    return 1; // No wall hit
}
//
//
double get_hinter(t_cub *cub, double ngl)
{
    double hx;
    double hy;
    double y_step;
    double x_step;
    int pxl;
//
    // Check if the ray is facing up or down
    y_step = TILE_SIZE;
    if (ngl > 0 && ngl < PI) // Facing down
        y_step = TILE_SIZE;
    else // Facing up
        y_step = -TILE_SIZE;
//
    // Calculate x_step based on the angle
    x_step = y_step / tan(ngl);
//
    // Calculate the initial horizontal intersection
    hy = floor(cub->plyr.plyr_y / TILE_SIZE) * TILE_SIZE;
    if (ngl > 0 && ngl < PI) // If the ray is facing down
        hy += TILE_SIZE; // Move to the next tile boundary down
//
    // pxl = (ngl > 0 && ngl < PI) ? 0 : -1; // Adjust for checking walls
    if (ngl > 0 && ngl < PI)
        pxl = 0;
    else
        pxl = -1;
//
    // Calculate the x-coordinate of the intersection based on the player's position and the angle
    hx = cub->plyr.plyr_x + (hy - cub->plyr.plyr_y) / tan(ngl);
//
    // Make sure x_step is negative when moving left, positive when moving right
    if ((ngl > PI / 2 && ngl < 3 * PI / 2) && x_step > 0) // Ray facing left
        x_step *= -1;
    if ((ngl < PI / 2 || ngl > 3 * PI / 2) && x_step < 0) // Ray facing right
        x_step *= -1;
//
    // Loop through intersections until a wall is hit
    while (wall_hit(hx, hy + pxl, cub)) {
        hx += x_step;
        hy += y_step;
    }
//
    // Return the distance to the intersection
    return (sqrt(pow(hx - cub->plyr.plyr_x, 2) + pow(hy - cub->plyr.plyr_y, 2)));
}
//
//TODO: ----> make this function do the same as get_hinter
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
	return (sqrt(pow(vx - cub->plyr.plyr_x, 2) + pow(vy - cub->plyr.plyr_y, 2)));
}


double calculate_wall_x(t_ray *ray)
{
    double wall_x;

    // Calculate wall_x based on hit type (horizontal or vertical)
    if (ray->hit == 1) {
        // Horizontal wall hit
        wall_x = fmod(ray->hit_x, TILE_SIZE); // Adjust TILE_SIZE to your grid/tile setup
    } else {
        // Vertical wall hit
        wall_x = fmod(ray->hit_y, TILE_SIZE);
    }
    return wall_x;
}

int get_texture_x(t_cub *cub, double wall_x)
{
    int tex_x;

    // Map wall_x to texture coordinate
    tex_x = (int)(wall_x * (cub->textures[0].w / TILE_SIZE)); // Adjust TEXTURE_WIDTH to texture resolution
    // printf("Inside get_texture_x: tex_x = %d\n", tex_x);
    return tex_x;
}


// RayCasting main Function
int raycaster(t_cub *cub)
{
    double h_inter;
    double v_inter;
    double wall_x;
    int tex_x;
    int nray;

    nray = 0;
    (void)tex_x;
    cub->ray.ray_ngl = angle_range(cub->plyr.angle - (cub->plyr.fov_rd / 2)); // Start ray angle from left FOV boundary
    // double ngl = cub->ray.ray_ngl + (cub->plyr.fov_rd / cub->var.s_w);
    // printf(GREEN "\t ray.angle :: %f\n" RES, cub->ray.ray_ngl);
    while (nray < cub->var.s_w)
    {
        cub->ray.hit = 0; // Reset hit flag for this ray
        cub->ray.ray_ngl = angle_range(cub->ray.ray_ngl);
        // printf(GREEN"\tRay angle :: %f\n"RES, cub->ray.ray_ngl);
        h_inter = get_hinter(cub, angle_range(cub->ray.ray_ngl)); // Get horizontal intersection
        v_inter = get_vinter(cub, angle_range(cub->ray.ray_ngl)); // Get vertical intersection
        // printf(RED"\tRay h_inter :: %f, v_inter :: %f\n"RES, h_inter, v_inter);
        if (v_inter <= h_inter)
            cub->ray.distance = v_inter; // Use vertical intersection distance
        else
        {
            cub->ray.distance = h_inter; // Use horizontal intersection distance
            cub->ray.hit = 1; // Mark that we hit a horizontal wall
        }
        // printf(YELLOW"\tthe Distance :: %f\n"RES, cub->ray.distance);
        cub->ray.hit_x = cub->plyr.plyr_x + cub->ray.distance * cos(cub->ray.ray_ngl);
        cub->ray.hit_y = cub->plyr.plyr_y + cub->ray.distance * sin(cub->ray.ray_ngl);
        // printf("intersection point(hit_x :: %f, hit_y :: %f)\n\t\t\t player_cordn(%d, %d)\n",cub->ray.hit_x ,cub->ray.hit_y,cub->plyr.plyr_x,cub->plyr.plyr_y);
        wall_x = calculate_wall_x(&cub->ray);
        tex_x = get_texture_x(cub,wall_x);
        // printf(CYAN "\t\t\n GGGGGG wall_x -------> %f tex_x -------> %d\n" RES, wall_x, tex_x);
        // Render the 3D wall slice for this ray
        ft_renderThreeD(cub, cub->ray.distance, nray, tex_x);
        //  put_rays(cub, cub->ray.distance, cub->plyr.plyr_x, cub->plyr.plyr_y, angle_range(cub->ray.ray_ngl));
        //  cub->ray.ray_ngl += ngl * 0.1;
         cub->ray.ray_ngl += (cub->plyr.fov_rd / cub->var.s_w);
         nray++;
    }
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
    return (0);

}
//
        //  printf("\t----ray-distnce--> %f\n",cub->ray.distance);
        // Increment ray angle and ray counter
        // cub->ray.ray_ngl += (cub->plyr.fov_rd / cub->var.s_w);