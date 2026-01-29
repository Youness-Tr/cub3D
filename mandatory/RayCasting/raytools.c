/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:03:40 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/12/17 15:10:11 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

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

int	wall_hit(float x, float y, t_cub *mlx)
{
	int	x_w;
	int	y_w;

	if (x < 0 || y < 0)
		return (0);
	x_w = floor(x / TILE_SIZE);
	y_w = floor(y / TILE_SIZE);
	if (y_w < 0 || y_w >= mlx->map.map_h || x_w < 0 || x_w >= mlx->map.map_w)
		return (0);
	if (mlx->map.map2d[y_w] && x_w < (int)strlen(mlx->map.map2d[y_w]))
	{
		if (mlx->map.map2d[y_w][x_w] == '1')
			return (0);
	}
	return (1);
}
