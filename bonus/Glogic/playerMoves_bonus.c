/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/15 14:16:07 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

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
		ft_exit(&cub->parse);
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

int	main_loop(t_cub *cub)
{
	mlx_clear_window(cub->mlxp, cub->mlx_w);
	mvp(cub);
	raycaster(cub);
	return (0);
}
