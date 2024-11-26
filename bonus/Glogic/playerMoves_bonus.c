/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/26 18:44:11 by youness          ###   ########.fr       */
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

void render_zoom(t_cub *cub)
{
    int image_x = ((cub->var.s_w )- cub->textures[4].w + 100) / 2;
    int image_y = (cub->var.s_h - cub->textures[4].h) - 290;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->textures[4].h; y++)
    {
        for (x = 0; x < cub->textures[4].w; x++)
        {
            color = *(unsigned int *)(cub->textures[4].addr + (y * cub->textures[4].len + x * (cub->textures[4].bpp / 8)));
            if (color  != 0xFF000000)
                my_mlx_pixel_put(&cub->img, image_x + x, image_y + y, color);
        }
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
	put_line(cub, 10, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP);
	shoot(cub);
	return (0);
}
