/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/27 21:57:00 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

int mv(int key, t_cub *cub)
{
    double x = cub->plyr.plyr_x;
    double y = cub->plyr.plyr_y;

    if (key == W) // Move up
    {
        x += cos(cub->plyr.angle) * P_SPEED;
        y += sin(cub->plyr.angle) * P_SPEED;
    }
    else if (key == S) // Move down
    {
        x -= cos(cub->plyr.angle) * P_SPEED;
        y -= sin(cub->plyr.angle) * P_SPEED;
    }
    else if (key == A) // Move left
    {
        x -= sin(cub->plyr.angle) * P_SPEED;
        y += cos(cub->plyr.angle) * P_SPEED;
    }
    else if (key == D) // Move right
    {
        x += sin(cub->plyr.angle) * P_SPEED;
        y -= cos(cub->plyr.angle) * P_SPEED;
    }
    else if (key == L_ARROW) // Rotate left
        cub->plyr.angle -= cub->plyr.rot * ROT_SPEED;
    else if (key == R_ARROW) // Rotate right
        cub->plyr.angle += cub->plyr.rot * ROT_SPEED;
    else if (key == ESC)
        exit(0);

    if (is_wall(cub, x, y))
    {
        cub->plyr.plyr_x = x;
        cub->plyr.plyr_y = y;
    }

        // printf("\t\t\t(%d, %d)\n", (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
    // render_2d(cub);
    // raycaster(cub);
    // put_line(cub, 50, (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
    return (0);
}

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
        exit(0);
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

void update_player_position(t_cub *cub)
{
    double new_x = cub->plyr.plyr_x;
    double new_y = cub->plyr.plyr_y;

    if (cub->move_forward)
    {
        new_x += cos(cub->plyr.angle) * P_SPEED;
        new_y += sin(cub->plyr.angle) * P_SPEED;
    }
    if (cub->move_backward)
    {
        new_x -= cos(cub->plyr.angle) * P_SPEED;
        new_y -= sin(cub->plyr.angle) * P_SPEED;
    }
    if (cub->move_left)
    {
        new_x -= sin(cub->plyr.angle) * P_SPEED;
        new_y += cos(cub->plyr.angle) * P_SPEED;
    }
    if (cub->move_right)
    {
        new_x += sin(cub->plyr.angle) * P_SPEED;
        new_y -= cos(cub->plyr.angle) * P_SPEED;
    }
    if (cub->rotate_left)
        cub->plyr.angle -= ROT_SPEED;
    if (cub->rotate_right)
        cub->plyr.angle += ROT_SPEED;

    // Check for collision before updating position
    if (is_wall(cub,new_x, new_y))
    {
        cub->plyr.plyr_x = new_x;
        cub->plyr.plyr_y = new_y;
    }
}

int main_loop(t_cub *cub)
{
    update_player_position(cub);
    raycaster(cub);
    return (0);
}
