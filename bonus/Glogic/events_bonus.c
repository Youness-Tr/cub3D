/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:50:16 by youness           #+#    #+#             */
/*   Updated: 2024/12/13 15:21:32 by ajabri           ###   ########.fr       */
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
	else if (key == E)
	{
		cub->mv = 50;
		cub->is_shooting = 1;
	}
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
	else if (key == E)
	{
		cub->mv = 0;
		cub->is_shooting = 0;
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == L_MOUS)
		cub->rotate_left = 1;
	if (button == R_MOUS)
		cub->rotate_right = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (button == L_MOUS)
		cub->rotate_left = 0;
	if (button == R_MOUS)
		cub->rotate_right = 0;
	return (0);
}

int	mouse_mv(int btn, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	(void)btn;
	if (cub->rotate_left)
		cub->plyr.angle -= ROT_SPEED;
	if (cub->rotate_right)
		cub->plyr.angle += ROT_SPEED;
	return (0);
}
