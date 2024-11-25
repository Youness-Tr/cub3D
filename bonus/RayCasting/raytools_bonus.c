/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytools_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:58:11 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/24 19:45:52 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

double	angle_range(double ngl)
{
	if (ngl < 0)
		ngl += (2 * PI);
	if (ngl > (2 * PI))
		ngl -= (2 * PI);
	return (ngl);
}

double	calculate_wall_x(t_ray *ray)
{
	double	wall_x;

	if (ray->hit == 1)
		wall_x = fmod(ray->hit_x, TILE_SIZE);
	else
		wall_x = fmod(ray->hit_y, TILE_SIZE);
	return (wall_x);
}

int	get_texture_x(t_cub *cub, double wall_x)
{
	int		tex_x;
	t_img	*texture;

	texture = get_texture(cub, cub->ray.hit);
	tex_x = (int)(wall_x * (texture->w / TILE_SIZE));
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

int get_door(t_cub *cub); // ! to the headerfile later on

int	wall_hit(float x, float y, t_cub *mlx)
{
	int	x_w;
	int	y_w;

	// mlx->ray.hit_door = 0;
	if (x < 0 || y < 0)
		return (0);
	x_w = floor(x / TILE_SIZE);
	y_w = floor(y / TILE_SIZE);
	if (y_w < 0 || y_w >= mlx->map.map_h || x_w < 0 || x_w >= mlx->map.map_w)
		return (0);
	if (mlx->map.map2d[y_w] && x_w < (int)strlen(mlx->map.map2d[y_w]))
	{
		if (mlx->map.map2d[y_w][x_w] == '1' || (mlx->map.map2d[y_w][x_w] == 'D')
		|| mlx->map.map2d[y_w][x_w] == 'C')
		{
			if (mlx->map.map2d[y_w][x_w] == 'D')
				mlx->ray.hit_door = 1;
			else if (mlx->map.map2d[y_w][x_w] == 'C')
				mlx->ray.hit_door = 2;
			return (0);
		}
	}
	return (1);
}



