/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:53:20 by youness           #+#    #+#             */
/*   Updated: 2024/11/26 16:00:14 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void shoot(t_cub *cub)
{
	if (cub->is_shooting)
    {
        cub->gun_frame++;
		usleep(50000);
        if (cub->gun_frame >= 18)
            cub->gun_frame = 0;
    }
	if (!cub->is_shooting && cub->gun_frame != 0)
	{
		cub->gun_frame--;
		usleep(50000);
	}
}

void render_weapon(t_cub *cub)
{
    int weapon_x = (cub->var.s_w - (cub->gun[cub->gun_frame].w)) / 2;
    int weapon_y = cub->var.s_h - cub->gun[cub->gun_frame].h;
    int x, y;
    unsigned int color;

    for (y = 0; y < cub->gun[cub->gun_frame].h; y++)
    {
        for (x = 0; x < cub->gun[cub->gun_frame].w; x++)
        {
            color = *(unsigned int *)(cub->gun[cub->gun_frame].addr + (y * cub->gun[cub->gun_frame].len + x * (cub->gun[cub->gun_frame].bpp / 8)));
            if (color  != 0xFF000000) // Check if the pixel is not fully transparent
            {
                my_mlx_pixel_put(&cub->img, weapon_x + x, weapon_y + y, color);
            }
        }
    }
}

void count_door_distances(t_cub *cub)
{
	int i;
	double player_x = cub->plyr.plyr_x / TILE_SIZE;
	double player_y = cub->plyr.plyr_y / TILE_SIZE;

	for (i = 0; i < cub->ndoors; i++)
	{
		cub->doors[i].distance = sqrt(pow(player_x - cub->doors[i].x / TILE_SIZE, 2) + pow(player_y - cub->doors[i].y / TILE_SIZE, 2));
		printf("distance to door %d is %f\n", i, cub->doors[i].distance);
	}
}

void handle_door_interaction(t_cub *cub)
{
    int i;

    i = 0;
    while (i < cub->ndoors)
    {
        count_door_distances(cub);
        if (cub->doors[i].distance <= DOOR_OPEN_DISTANCE)
        {
            cub->doors[i].open = 1;
            cub->default_door.open = 0;
            cub->default_door.frame = MAX_DOOR;
            cub->index = 1;
            cub->doors[i].frame++;
            if (cub->doors[i].frame > 21)
                cub->doors[i].frame = 21;
            cub->index = i; // !to remove
        }
        else
        {
            cub->doors[i].open = 0;
            cub->index = 0;
            cub->doors[i].frame--;
            cub->default_door.frame--;
            if (cub->default_door.frame < 1)
                cub->default_door.frame = 1;
            if (cub->doors[i].frame < 1)
                cub->doors[i].frame = 1;
        }
        i++;
    }
    i = 0;
    while (i < cub->ndoors)
        i++;
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