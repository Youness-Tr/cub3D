/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/28 10:49:16 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	set_pos(t_cub *cub, double x, double y)
{
	if (cub->rotate_left)
		cub->plyr.angle -= ROT_SPEED;
	if (cub->rotate_right)
		cub->plyr.angle += ROT_SPEED;
	if (is_wall(cub, x, cub->plyr.plyr_y))
		cub->plyr.plyr_x = x;
	else
	{
		if (is_wall(cub, cub->plyr.plyr_x, y))
			cub->plyr.plyr_y = y;
	}
	if (is_wall(cub, cub->plyr.plyr_x, y))
		cub->plyr.plyr_y = y;
	else
	{
		if (is_wall(cub, x, cub->plyr.plyr_y))
			cub->plyr.plyr_x = x;
	}
}

void	mvp(t_cub *cub)
{
	cub->var.new_x = cub->plyr.plyr_x;
	cub->var.new_y = cub->plyr.plyr_y;
	if (cub->move_forward)
	{
		cub->var.new_x += cos(cub->plyr.angle) * P_SPEED;
		cub->var.new_y += sin(cub->plyr.angle) * P_SPEED;
	}
	if (cub->move_backward)
	{
		cub->var.new_x -= cos(cub->plyr.angle) * P_SPEED;
		cub->var.new_y -= sin(cub->plyr.angle) * P_SPEED;
	}
	if (cub->move_left)
	{
		cub->var.new_x += sin(cub->plyr.angle) * P_SPEED;
		cub->var.new_y -= cos(cub->plyr.angle) * P_SPEED;
	}
	if (cub->move_right)
	{
		cub->var.new_x -= sin(cub->plyr.angle) * P_SPEED;
		cub->var.new_y += cos(cub->plyr.angle) * P_SPEED;
	}
	set_pos(cub, cub->var.new_x, cub->var.new_y);
}

void	render_zoom(t_cub *cub)
{
	int				image_x;
	int				image_y;
	unsigned int	color;

	image_x = ((cub->var.s_w) - cub->textures[ZOOM_TEXTURE].w + 100) / 2;
	image_y = (cub->var.s_h - cub->textures[ZOOM_TEXTURE].h) - 290;
	cub->var.y = 0;
	while (cub->var.y < cub->textures[ZOOM_TEXTURE].h)
	{
		cub->var.x = 0;
		while (cub->var.x < cub->textures[ZOOM_TEXTURE].w)
		{
			color = *(unsigned int *)(cub->textures[ZOOM_TEXTURE].addr
					+ (cub->var.y * cub->textures[ZOOM_TEXTURE].len + cub->var.x
						* (cub->textures[ZOOM_TEXTURE].bpp / 8)));
			if (color != 0xFF000000)
			{
				my_mlx_pixel_put(&cub->img, image_x + cub->var.x, image_y
					+ cub->var.y, color);
			}
			cub->var.x++;
		}
		cub->var.y++;
	}
}

int	main_loop(t_cub *cub)
{
	mlx_clear_window(cub->mlxp, cub->mlx_w);
	mvp(cub);
	raycaster(cub);
	render_mini_2d(cub);
	handle_door_interaction(cub, 0);
	render_zoom(cub);
	render_weapon(cub);
	shoot(cub);
	return (0);
}

	// put_line(cub, 10, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP);