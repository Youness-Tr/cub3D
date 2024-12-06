/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2d_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:43 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/06 17:25:46 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

// void	render_square(t_cub *cub, int color)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < MINI_TILE)
// 	{
// 		x = 0;
// 		while (x < MINI_TILE)
// 		{
// 		printf("\tHERE\n");
// 			my_mlx_pixel_put(&cub->img, ((cub->topv.i * MINI_TILE))
// 				+ x, ((cub->topv.j * MINI_TILE)  + y), color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	render_circle(t_cub *cub, int color)
// {
// 	int	x;
// 	int	y;
// 	int	radius;

// 	radius = PLAYER_RADIUS / MINI_TILE;
// 	y = -radius;
// 	while (y <= radius)
// 	{
// 		x = -radius;
// 		while (x <= radius)
// 		{
// 			if (x * x + y * y <= radius * radius)
// 			{
// 				my_mlx_pixel_put(&cub->img, cub->plyr.plyr_x / MINI_TILE + x,
// 					cub->plyr.plyr_y / MINI_TILE + y, color);
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void render_topv(t_cub *cub)
// {
// 	cub->topv.range = PLAYER_RANGE / TILE_SIZE;
// 	int start_x;
// 	int end_x;
// 	int start_y;
// 	int end_y;
// 	start_x = cub->plyr.plyr_x/ TILE_SIZE  - cub->topv.range;
// 	if (start_x < 0)
// 		start_x = 0;
// 	end_x = cub->plyr.plyr_x/ TILE_SIZE + cub->topv.range;
// 	if (end_x >= cub->map.map_w)
// 		end_x = cub->map.map_w;
// 	// printf("topv->range == %d\n", cub->topv.range);
// 	// printf("start_x == %d , end_x = %d\n", start_x, end_x);
// 	// printf("p_x == %d , p_y = %d\n", cub->plyr.plyr_x, cub->plyr.plyr_y);
// 	start_y = cub->plyr.plyr_y/ TILE_SIZE - cub->topv.range;
// 	if (start_y < 0)
// 		start_y = 0;
// 	end_y = cub->plyr.plyr_y/ TILE_SIZE + cub->topv.range;
// 	if (end_y >= cub->map.map_h)
// 		end_y = cub->map.map_h;
// 	int dist;

// 	cub->topv.j = start_y;
// 	while (cub->topv.j <= end_y)
// 	{
// 		cub->topv.i = start_x;
// 		while (cub->topv.i <= end_x)
// 		{
// 		// printf("hello\n");
// 			dist = abs(cub->plyr.plyr_x/ TILE_SIZE - cub->topv.i) + abs(cub->plyr.plyr_y/ TILE_SIZE  - cub->topv.j);
// 				// printf("hello %d\n", dist);
// 			if (dist <= PLAYER_RANGE)
// 			{
// 				if (cub->map.map2d[cub->topv.j][cub->topv.i] == '1')
// 				{

// 					// printf("\tHERE\n");
// 					render_square(cub, 0x003049);
// 				}
// 				else if (cub->map.map2d[cub->topv.j][cub->topv.i] == '0' || cub->map.map2d[cub->topv.j][cub->topv.i] == 'P')
// 					render_square(cub, 0xdad8d8);
// 				else if (cub->map.map2d[cub->topv.j][cub->topv.i] == 'D')
// 				render_square(cub, 0xfca311);
// 			}
// 			cub->topv.i++;
// 		}
// 		cub->topv.j++;
// 	}
// 	render_circle(cub, 0xff9505);
// 	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
// }


// void	render_mini_2d(t_cub *cub)
// {
// 	cub->topv.j = 0;
// 	cub->map.map2d[cub->parse.player_x][cub->parse.player_y] = 'P';
// 	cub->topv.factor = (float)(cub->var.s_w * MINI_MAP) / cub->map.map_w + 1;
// 	while (cub->topv.j < cub->map.map_h + 1)
// 	{
// 		cub->topv.i = 0;
// 		while (cub->topv.i < cub->map.map_w + 1)
// 		{
// 			if (cub->map.map2d[cub->topv.j][cub->topv.i] == '1')
// 				render_square(cub, 0x003049);
// 			else if (cub->map.map2d[cub->topv.j][cub->topv.i] == '0'
// 				|| cub->map.map2d[cub->topv.j][cub->topv.i] == 'P')
// 			{
// 				render_square(cub, 0xffffff);
// 			}
// 			else if (cub->map.map2d[cub->topv.j][cub->topv.i] == 'D')
// 			{
// 				render_square(cub, 0x00FF00);
// 			}
// 			cub->topv.i++;
// 		}
// 		cub->topv.j++;
// 	}
// 	render_circle(cub, 0xFF0000);
// 	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
// }


/************************************************ */

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

void render_minimap(t_cub *cub)
{
    int start_x, start_y, end_x, end_y;
    int map_x, map_y;
    int render_x, render_y;

    // Define minimap bounds (top-left corner offset + padding)
    int offset_x = 1;
    int offset_y = 1;

    // Calculate visible map range based on minimap dimensions
    start_x = cub->plyr.plyr_x / TILE_SIZE - PLAYER_RANGE / TILE_SIZE;
    start_y = cub->plyr.plyr_y / TILE_SIZE - PLAYER_RANGE / TILE_SIZE;

    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;

    end_x = start_x + (cub->var.s_w * MINI_MAP) / MINI_TILE;
    end_y = start_y + (cub->var.s_h * MINI_MAP) / MINI_TILE;

    if (end_x >= cub->map.map_w) end_x = cub->map.map_w + 1;
    if (end_y >= cub->map.map_h) end_y = cub->map.map_h + 1;

    // Render map tiles
    for (map_y = start_y; map_y < end_y; map_y++)
    {
        for (map_x = start_x; map_x < end_x; map_x++)
        {
            // Convert map position to minimap position
            render_x = offset_x + (map_x - start_x) * MINI_TILE;
            render_y = offset_y + (map_y - start_y) * MINI_TILE;

            // Determine tile color
            if (cub->map.map2d[map_y][map_x] == '1')
                render_fixed_square(cub, render_x, render_y, 0x003049); // Walls
            else if (cub->map.map2d[map_y][map_x] == '0' || cub->map.map2d[map_y][map_x] == 'P')
                render_fixed_square(cub, render_x, render_y, 0xdad8d8); // Floor
            else if (cub->map.map2d[map_y][map_x] == 'D')
                render_fixed_square(cub, render_x, render_y, 0xfca311); // Doors
        }
    }

    // Render player as a circle
    render_fixed_circle(
        cub,
        offset_x + ((cub->plyr.plyr_x / TILE_SIZE - start_x) * MINI_TILE),
        offset_y + ((cub->plyr.plyr_y / TILE_SIZE - start_y) * MINI_TILE),
        0xff9505
    );

    // Draw minimap to the window
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}
