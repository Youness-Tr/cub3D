/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:38:47 by kali              #+#    #+#             */
/*   Updated: 2024/09/27 16:08:54 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void create_img(t_cub *cub)
{
    // t_img mg;
    // t_map mp;

    // mg = cub->img;
    // mp = cub->map;
    cub->img.img = mlx_new_image(cub->mlxp, cub->map.map_w *TILE_SIZE, cub->map.map_h *TILE_SIZE);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, &cub->img.len,
								&cub->img.endian);
    // mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);

}

void render_square(t_img *img, int x_start, int y_start, int size, int color)
{
    int x;
    int y;

    y = 0;
    while (y < size)
    {
        x = 0;
        while (x < size)
        {
            my_mlx_pixel_put(img, x_start + x, y_start + y, color);
            x++;
        }
        y++;
    }
}

void render_circle(t_img *img, int cx, int cy, int radius, int color)
{
    int x;
    int y;

    y = -radius;
    while (y <= radius)
    {
        x = -radius;
        while (x <= radius)
        {
            // Check if the point (cx + x, cy + y) is inside the circle
            if (x * x + y * y <= radius * radius)
            {
                my_mlx_pixel_put(img, cx + x, cy + y, color);
            }
            x++;
        }
        y++;
    }
}

static void	put_mini_player(t_cub *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLAYER_RADIUS)
	{
		j = 0;
		while (j < PLAYER_RADIUS)
		{
			my_mlx_pixel_put(&data->img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void render_map(t_cub *cub)
{
    t_map map;
    int x;
    int y;

    y = 0;
    map = cub->map;
    while (y < map.map_h)
    {
        x = 0;
        while (x < map.map_w)
        {
            if (map.map2d[y][x] == '1')
            {
                render_square(&cub->img, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 1, 0x964B00);
            }
            else if (map.map2d[y][x] == '0' || map.map2d[y][x] == 'P')
            {
                render_square(&cub->img, x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE - 1, 0xFFFFFF);
                // my_mlx_pixel_put(&cub->img,x * TILE_SIZE, y * TILE_SIZE, 0x000000);
                // render floors;
            }
            x++;
        }
        y++;
    }
    // render_circle(&cub->img, cub->plyr.px - TILE_SIZE / 4, cub->plyr.py - TILE_SIZE / 4, TILE_SIZE / 4, 0xFF0000);
    put_mini_player(cub, (int)cub->plyr.px, (int)cub->plyr.py, 0x000000);

    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}