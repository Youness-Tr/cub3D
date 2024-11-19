/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/19 14:36:31 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void find_door_cordn(t_cub *o);

void handle_door_interaction(t_cub *cub)
{
    double player_x = cub->plyr.plyr_x / TILE_SIZE;
    double player_y = cub->plyr.plyr_y / TILE_SIZE;
    double door_x = cub->door.x;
    double door_y = cub->door.y;

    double distance = sqrt(pow(player_x - door_x, 2) + pow(player_y - door_y, 2));

    if (distance <= DOOR_OPEN_DISTANCE)
    {
        cub->door.open = 1; // Open the door
		// find_door_cordn(cub);
		// cub->map.map2d[cub->door.y][cub->door.x] = 'E'; // Change map to open door
		cub->door.frame = 9;
	}
    else
    {
        cub->door.open = 0; // Close the door
		// find_door_cordn(cub);
		cub->door.frame = 6;
        cub->map.map2d[cub->door.y][cub->door.x] = 'D'; // Change map to closed door
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
		cub->gun_frame = 5;
	// else if (key == O)
	// {
	// 	 handle_door_interaction(cub);
	// }
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
		printf("E key released\n");
		cub->gun_frame = 4;
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
    int weapon_x = (cub->var.s_w - (cub->textures[cub->gun_frame].w)) / 2;
    int weapon_y = cub->var.s_h - cub->textures[cub->gun_frame].h;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->textures[cub->gun_frame].h; y++)
    {
        for (x = 0; x < cub->textures[cub->gun_frame].w; x++)
        {
            color = *(unsigned int *)(cub->textures[cub->gun_frame].addr + (y * cub->textures[cub->gun_frame].len + x * (cub->textures[cub->gun_frame].bpp / 8)));
            if ((color & 0xFF000000) != 0xFF000000) // Check if the pixel is not fully transparent
            {
                my_mlx_pixel_put(&cub->img, weapon_x + x, weapon_y + y, color);
            }
        }
    }
}

void render_zoom(t_cub *cub)
{
    int image_x = ((cub->var.s_w )- cub->textures[7].w) / 3;
    int image_y = (cub->var.s_h - cub->textures[7].h) / 2;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->textures[7].h; y++)
    {
        for (x = 0; x < cub->textures[7].w; x++)
        {
            color = *(unsigned int *)(cub->textures[7].addr + (y * cub->textures[7].len + x * (cub->textures[7].bpp / 8)));
            if ((color & 0xFF000000) != 0xFF000000) // Check if the pixel is not fully transparent
            {
                my_mlx_pixel_put(&cub->img, image_x + x, image_y + y, color);
            }
        }
    }
}



void put_rays(t_cub *cub, int len, int x, int y, float ngl);
int	main_loop(t_cub *cub)
{
	mlx_clear_window(cub->mlxp, cub->mlx_w);
	mvp(cub);
	raycaster(cub);
	handle_door_interaction(cub);
	render_zoom(cub);
	render_weapon(cub);
	render_mini_2d(cub);
	put_line(cub, 18, cub->plyr.plyr_x * MINI_MAP, cub->plyr.plyr_y * MINI_MAP);
	return (0);
}
