/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/13 18:24:00 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	set_pos(t_cub *cub, double x, double y)
{
	if (cub->rotate_left)
		cub->plyr.angle = angle_range(cub->plyr.angle - ROT_SPEED);
	if (cub->rotate_right)
		cub->plyr.angle = angle_range(cub->plyr.angle + ROT_SPEED);
	if (is_wall(cub, x, cub->plyr.plyr_y))
		cub->plyr.plyr_x = x;
	if (is_wall(cub, cub->plyr.plyr_x, y))
		cub->plyr.plyr_y = y;
}

void	mvp(t_cub *cub)
{
	cub->var.new_x = cub->plyr.plyr_x;
	cub->var.new_y = cub->plyr.plyr_y;
	cub->plyr.angle = angle_range(cub->plyr.angle);
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
	printf("player x = %.2f, y = %.2f\n", cub->var.new_x, cub->var.new_y);
	set_pos(cub, cub->var.new_x, cub->var.new_y);
}

void	render_zoom(t_cub *cub)
{
	int				image_x;
	int				image_y;
	unsigned int	color;

	image_x = ((cub->var.s_w) - cub->textures[ZOOM_TEXTURE].w) / 2;
	image_y = ((cub->var.s_h - cub->textures[ZOOM_TEXTURE].h) + 50) / 2;
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
	cub->plyr.angle = angle_range(cub->plyr.angle);
	mvp(cub);
	raycaster(cub);
	render_minimap(cub);
	handle_door_interaction(cub, 0);
	render_zoom(cub);
	render_weapon(cub);
	if (cub->var.shoot)
		shoot(cub);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
	return (0);
}
