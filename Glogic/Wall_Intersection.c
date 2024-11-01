/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_Intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:43:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/01 18:49:55 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

int is_wall(t_cub *cub,  double x, int y)
{
    /*TODO:
            I need to fix some issues by improving this function.
            make the check x and x + 5 and y and y + 5 is valide or no
    */
    // x = floor()
    double px;
    double py;

    px = floor(x / TILE_SIZE);
    py = floor(y / TILE_SIZE);
    if (px > cub->map.map_w || px < 0 || py < 0 || py > cub->map.map_h)
    {
        return (0);
    }
    if (cub->map.map2d[(int)py][(int)px] == '1')
        return (0);
    return (1);
}

