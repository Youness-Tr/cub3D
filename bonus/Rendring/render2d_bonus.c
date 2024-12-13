/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/13 17:03:58 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void render_fixed_square(t_cub *cub, int x, int y, int color)
{
    int i, j;

    j = 0;
    while (j < MINI_TILE)
    {
        i = 0;
        while (i < MINI_TILE)
        {
            my_mlx_pixel_put(&cub->img, x + i, y + j, color);
            i++;
        }
        j++;
    }
}

void render_fixed_circle(t_cub *cub, int cx, int cy, int color)
{
    int x, y;
    int radius = PLAYER_RADIUS / MINI_TILE;

    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(&cub->img, cx + x, cy + y, color);
            }
            x++;
        }
        y++;
    }
}

void set_range(t_cub *cub)
{
    cub->var.start_x = cub->plyr.plyr_x / TILE_SIZE - PLAYER_RANGE / TILE_SIZE;
    cub->var.start_y = cub->plyr.plyr_y / TILE_SIZE - PLAYER_RANGE / TILE_SIZE;
    if (cub->var.start_x < 0)
        cub->var.start_x = 0;
    if (cub->var.start_y < 0)
        cub->var.start_y = 0;
    cub->var.end_x = cub->var.start_x + (cub->var.s_w * MINI_MAP) / MINI_TILE;
    cub->var.end_y = cub->var.start_y + (cub->var.s_h * MINI_MAP) / MINI_TILE;
    if (cub->var.end_x >= cub->map.map_w)
        cub->var.end_x = cub->map.map_w + 1;
    if (cub->var.end_y >= cub->map.map_h)
        cub->var.end_y = cub->map.map_h + 1;
}

void render_minimap(t_cub *cub)
{
    set_range(cub);
    cub->var.map_y = cub->var.start_y;
    while (cub->var.map_y < cub->var.end_y)
    {
        cub->var.map_x = cub->var.start_x;
        while (cub->var.map_x < cub->var.end_x)
        {
            cub->var.render_x = (cub->var.map_x - cub->var.start_x) * MINI_TILE;
            cub->var.render_y = (cub->var.map_y - cub->var.start_y) * MINI_TILE;
            if (cub->map.map2d[cub->var.map_y][cub->var.map_x] == '1')
                render_fixed_square(cub, cub->var.render_x + 1, cub->var.render_y + 1, 0x003049);
            else if (cub->map.map2d[cub->var.map_y][cub->var.map_x] == '0' || cub->map.map2d[cub->var.map_y][cub->var.map_x] == 'P')
                render_fixed_square(cub, cub->var.render_x + 1, cub->var.render_y + 1, 0xdad8d8);
            else if (cub->map.map2d[cub->var.map_y][cub->var.map_x] == 'D')
                render_fixed_square(cub, cub->var.render_x + 1, cub->var.render_y + 1, 0xfca311);
            cub->var.map_x++;
        }
        cub->var.map_y++;
    }
    render_fixed_circle(
        cub,
        ((cub->plyr.plyr_x / TILE_SIZE - cub->var.start_x) * MINI_TILE),
        ((cub->plyr.plyr_y / TILE_SIZE - cub->var.start_y) * MINI_TILE),
        0xff9505
    );
}
