/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/16 12:01:57 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

int	key_press(int key, t_cub *cub)
{
	if (key == W)
		cub->move_forward = 1;
	else if (key == S)
		cub->move_backward = 1;
	else if (key == A)
		cub->move_left = 1;
	else if (key == D)
		cub->move_right = 1;
	else if (key == L_ARROW)
		cub->rotate_left = 1;
	else if (key == R_ARROW)
		cub->rotate_right = 1;
	else if (key == ESC)
		_close_window(cub);
	return (0);
}

int	key_release(int key, t_cub *cub)
{
	if (key == W)
		cub->move_forward = 0;
	else if (key == S)
		cub->move_backward = 0;
	else if (key == A)
		cub->move_left = 0;
	else if (key == D)
		cub->move_right = 0;
	else if (key == L_ARROW)
		cub->rotate_left = 0;
	else if (key == R_ARROW)
		cub->rotate_right = 0;
	return (0);
}

void	set_pos(t_cub *cub, double x, double y)
{
	if (cub->rotate_left)
		cub->plyr.angle -= ROT_SPEED;
	if (cub->rotate_right)
		cub->plyr.angle += ROT_SPEED;
	if (is_wall(cub, x, y))
	{
		cub->plyr.plyr_x = x;
		cub->plyr.plyr_y = y;
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

int	main_loop(t_cub *cub)
{
	mlx_clear_window(cub->mlxp, cub->mlx_w);
	mvp(cub);
	raycaster(cub);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
	return (0);
}
