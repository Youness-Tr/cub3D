/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Wall_Intersection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:43:37 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 10:45:45 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

int is_wall(t_cub *cub,  double x, int y)
{
    // x = floor()
    double px;
    double py;

    px = floor(x / TILE_SIZE);
    py = floor(y / TILE_SIZE);
    if (px > cub->map.map_w || px < 0 || py < 0 || py > cub->map.map_h)
    {
        printf("Hello\n");
        return (0);
    }
    if (cub->map.map2d[(int)py][(int)px] == '1')
    {
        printf("Hello map == 1\n");
        return (0);
    }
    return (1);
}

