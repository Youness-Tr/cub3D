/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/06 19:16:05 by kali             ###   ########.fr       */
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
        exit(0); // khass free hnaya
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
    double move_step = P_SPEED;

    if (cub->move_forward)
    {
        new_x += cos(cub->plyr.angle) * move_step;
        new_y += sin(cub->plyr.angle) * move_step;
    }
    if (cub->move_backward)
    {
        new_x -= cos(cub->plyr.angle) * move_step;
        new_y -= sin(cub->plyr.angle) * move_step;
    }
    if (cub->move_left)
    {
        new_x -= sin(cub->plyr.angle) * move_step;
        new_y += cos(cub->plyr.angle) * move_step;
    }
    if (cub->move_right)
    {
        new_x += sin(cub->plyr.angle) * move_step;
        new_y -= cos(cub->plyr.angle) * move_step;
    }
    if (cub->rotate_left)
    {
        cub->plyr.angle -= ROT_SPEED;
    }
    if (cub->rotate_right)
    {
        cub->plyr.angle += ROT_SPEED;
    }

    // Check for wall collisions and slide along walls
    if (is_wall(cub, new_x, cub->plyr.plyr_y))
    {
        cub->plyr.plyr_x = new_x;
    }
    else
    {
        // Slide along the y-axis if x-axis collision detected
        if (is_wall(cub, cub->plyr.plyr_x, new_y))
        {
            cub->plyr.plyr_y = new_y;
        }
    }

    if (is_wall(cub, cub->plyr.plyr_x, new_y))
    {
        cub->plyr.plyr_y = new_y;
    }
    else
    {
        // Slide along the x-axis if y-axis collision detected
        if (is_wall(cub, new_x, cub->plyr.plyr_y))
        {
            cub->plyr.plyr_x = new_x;
        }
    }
}



void ft_render_wepon(t_cub *cub)
{
    void *wepon;
    int x, y;
    wepon = mlx_xpm_file_to_image(cub->mlxp, "./Assets/Textures/wepon.xpm", &x, &y);
    if (!wepon)
        ft_error("Error : wepon is not loaded\n");
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, wepon, cub->plyr.plyr_x, cub->plyr.plyr_y);
}

int main_loop(t_cub *cub)
{
    update_player_position(cub);
    raycaster(cub);
    // render_mini_2d(cub);
    // ft_render_wepon(cub);

    return (0);
}


/*This function should be removed */
// int mv(int key, t_cub *cub)
// {
//     double x = cub->plyr.plyr_x;
//     double y = cub->plyr.plyr_y;

//     if (key == W) // Move up
//     {
//         x += cos(cub->plyr.angle) * P_SPEED;
//         y += sin(cub->plyr.angle) * P_SPEED;
//     }
//     else if (key == S) // Move down
//     {
//         x -= cos(cub->plyr.angle) * P_SPEED;
//         y -= sin(cub->plyr.angle) * P_SPEED;
//     }
//     else if (key == A) // Move left
//     {
//         x -= sin(cub->plyr.angle) * P_SPEED;
//         y += cos(cub->plyr.angle) * P_SPEED;
//     }
//     else if (key == D) // Move right
//     {
//         x += sin(cub->plyr.angle) * P_SPEED;
//         y -= cos(cub->plyr.angle) * P_SPEED;
//     }
//     else if (key == L_ARROW) // Rotate left
//         cub->plyr.angle -= cub->plyr.rot * ROT_SPEED;
//     else if (key == R_ARROW) // Rotate right
//         cub->plyr.angle += cub->plyr.rot * ROT_SPEED;
//     else if (key == ESC)
//         exit(0);

//     // if (is_wall(cub, x, y))
//     // {
//         cub->plyr.plyr_x = x;
//         cub->plyr.plyr_y = y;
//     // }

//         // printf("\t\t\t(%d, %d)\n", (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
//     // render_2d(cub);
//     raycaster(cub);
//     return (0);
// }