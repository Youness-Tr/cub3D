/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playerMoves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:41:28 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 11:53:00 by ajabri           ###   ########.fr       */
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
    raycaster(cub);
    put_line(cub, 50, (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
    return (0);
}
