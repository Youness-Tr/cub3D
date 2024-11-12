/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/12 09:39:37 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

int key_press(int key, t_cub *cub)
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
        exit(0); // !khass free hnaya
    return (0);
}

int key_release(int key, t_cub *cub)
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

void mvp(t_cub *cub)
{
    double new_x = cub->plyr.plyr_x;
    double new_y = cub->plyr.plyr_y;

    if (cub->move_forward)
    {
        new_x += cos(cub->plyr.angle) *P_SPEED;
        new_y += sin(cub->plyr.angle) *P_SPEED;
    }
    if (cub->move_backward)
    {
        new_x -= cos(cub->plyr.angle) *P_SPEED;
        new_y -= sin(cub->plyr.angle) *P_SPEED;
    }
    if (cub->move_left)
    {
        new_x -= sin(cub->plyr.angle) *P_SPEED;
        new_y += cos(cub->plyr.angle) *P_SPEED;
    }
    if (cub->move_right)
    {
        new_x += sin(cub->plyr.angle) *P_SPEED;
        new_y -= cos(cub->plyr.angle) *P_SPEED;
    }
    if (cub->rotate_left)
    {
        cub->plyr.angle -= ROT_SPEED;
    }
    if (cub->rotate_right)
    {
        cub->plyr.angle += ROT_SPEED;
    }

    // ?Check for wall collisions and slide along walls
    if (is_wall(cub, new_x, cub->plyr.plyr_y))
        cub->plyr.plyr_x = new_x;
    else
    {
        // *Slide along the y-axis if x-axis collision detected
        if (is_wall(cub, cub->plyr.plyr_x, new_y))
            cub->plyr.plyr_y = new_y;
    }
    if (is_wall(cub, cub->plyr.plyr_x, new_y))
        cub->plyr.plyr_y = new_y;
    else
    {
        // *Slide along the x-axis if y-axis collision detected
        if (is_wall(cub, new_x, cub->plyr.plyr_y))
            cub->plyr.plyr_x = new_x;
    }
}
//TODO

int main_loop(t_cub *cub)
{
    mlx_clear_window(cub->mlxp, cub->mlx_w);
    mvp(cub);
    raycaster(cub);
    return (0);
}
