/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/25 19:29:41 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

//! remove unused variabe like index
void handle_door_interaction(t_cub *cub)
{
    double player_x = cub->plyr.plyr_x / TILE_SIZE;
    double player_y = cub->plyr.plyr_y / TILE_SIZE;
    int i;

    i = 0;
    while (i < cub->ndoors)
    {
        cub->doors[i].distance = sqrt(pow(player_x - cub->doors[i].x/ TILE_SIZE, 2) + pow(player_y - cub->doors[i].y/TILE_SIZE, 2));
        if (cub->doors[i].distance <= DOOR_OPEN_DISTANCE)
        {
            cub->doors[i].open = 1;
            cub->doors[i].frame++;
			if (cub->doors[i].frame > 21)
				cub->doors[i].frame = 21;
			cub->index = i;
        }
        else
        {
            cub->doors[i].open = 0;
			// cub->index = i;
            cub->doors[i].frame--;
			if (cub->doors[i].frame < 1)
				cub->doors[i].frame = 1;
        }
        i++;
    }
}

void set_gun(t_cub *cub, char *file)
{
	cub->textures[4].img = mlx_xpm_file_to_image(cub->mlxp, file, &cub->textures[4].w, &cub->textures[4].h);
	if (!cub->textures[4].img)
	{
		ft_errorv2(&cub->parse, "Error: Could not load texture");
		_close_window(cub);
	}
}

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
		cub->is_shooting = 1;
	}
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
	else if (key == E)
	{
		cub->is_shooting = 0;
	}
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
int mouse_press(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
    if (button == L_MOUS) {
        cub->rotate_left = 1;
    }
    if (button == R_MOUS) {
        cub->rotate_right = 1;
    }
    return (0);
}

int mouse_release(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
    if (button == L_MOUS) {
        cub->rotate_left = 0;
    }
    if (button == R_MOUS) {
        cub->rotate_right = 0;
    }
    return (0);
}

int mouse_mv(int btn, int x, int y, t_cub *cub)
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

void render_weapon(t_cub *cub)
{
    int weapon_x = (cub->var.s_w - (cub->gun[cub->gun_frame].w)) / 2;
    int weapon_y = cub->var.s_h - cub->gun[cub->gun_frame].h;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->gun[cub->gun_frame].h; y++)
    {
        for (x = 0; x < cub->gun[cub->gun_frame].w; x++)
        {
            color = *(unsigned int *)(cub->gun[cub->gun_frame].addr + (y * cub->gun[cub->gun_frame].len + x * (cub->gun[cub->gun_frame].bpp / 8)));
            if (color  != 0xFF000000) // Check if the pixel is not fully transparent
            {
                my_mlx_pixel_put(&cub->img, weapon_x + x, weapon_y + y, color);
            }
        }
    }
}

void render_zoom(t_cub *cub)
{
    int image_x = ((cub->var.s_w )- cub->textures[5].w + 100) / 2;
    int image_y = (cub->var.s_h - cub->textures[5].h) - 290;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->textures[5].h; y++)
    {
        for (x = 0; x < cub->textures[5].w; x++)
        {
            color = *(unsigned int *)(cub->textures[5].addr + (y * cub->textures[5].len + x * (cub->textures[5].bpp / 8)));
            if ((color & 0xFF000000) != 0xFF000000) // Check if the pixel is not fully transparent
            {
                my_mlx_pixel_put(&cub->img, image_x + x, image_y + y, color);
            }
        }
    }
}

// *this function to merge
void shoot(t_cub *cub)
{
	if (cub->is_shooting)
    {
        cub->gun_frame++;
		usleep(50000);
        if (cub->gun_frame >= 18)
            cub->gun_frame = 0;
    }
	if (!cub->is_shooting && cub->gun_frame != 0)
	{
		cub->gun_frame--;
		usleep(50000);
	}
}

int	main_loop(t_cub *cub)
{
	// mlx_clear_window(cub->mlxp, cub->mlx_w);
	mvp(cub);
	raycaster(cub);
	render_mini_2d(cub);
	handle_door_interaction(cub);
	render_zoom(cub);
	render_weapon(cub);
	put_line(cub, 10, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP);
	shoot(cub);
	return (0);
}
