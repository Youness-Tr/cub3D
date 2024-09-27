/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:32:43 by kali              #+#    #+#             */
/*   Updated: 2024/09/23 16:38:26 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

#include <math.h>

// Function to check if the player collides with walls
int check_collision(t_cub *cub, float new_px, float new_py)
{
    // Calculate the tile positions based on the new player position
    int tile_x = (int)(new_px / TILE_SIZE);
    int tile_y = (int)(new_py / TILE_SIZE);

    // Check the surrounding tiles for walls
    for (int dy = -1; dy <= 1; dy++)
    {
        for (int dx = -1; dx <= 1; dx++)
        {
            int check_x = tile_x + dx;
            int check_y = tile_y + dy;

            // Ensure we are within map boundaries
            if (check_x >= 0 && check_x < cub->map.map_w && check_y >= 0 && check_y < cub->map.map_h)
            {
                // If there's a wall, perform collision checking
                if (cub->map.map2d[check_y][check_x] == '1')
                {
                    // Calculate the closest point on the wall
                    float closest_x = fmax(check_x * TILE_SIZE, fmin(new_px, (check_x + 1) * TILE_SIZE));
                    float closest_y = fmax(check_y * TILE_SIZE, fmin(new_py, (check_y + 1) * TILE_SIZE));

                    // Calculate the distance from the player's center to the closest point
                    float distance_x = new_px - closest_x;
                    float distance_y = new_py - closest_y;

                    // Check if the distance is less than the radius
                    if ((distance_x * distance_x + distance_y * distance_y) < (PLAYER_RADIUS * PLAYER_RADIUS))
                    {
                        return 1; // Collision detected
                    }
                }
            }
        }
    }
    return 0; // No collision
}


int mv(int key, t_cub *cub)
{
    float new_px = cub->plyr.px;
    float new_py = cub->plyr.py;

    if (key == R_ARROW)
        cub->plyr.angle += cub->plyr.rot * ROT_SPEED;
    else if (key == L_ARROW)
        cub->plyr.angle -= cub->plyr.rot * ROT_SPEED;
    else if (key == W) // Move forward
    {
        new_px += cos(cub->plyr.angle) * cub->plyr.plyr_speed;
        new_py += sin(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == S) // Move backward
    {
        new_px -= cos(cub->plyr.angle) * cub->plyr.plyr_speed;
        new_py -= sin(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == A) // Move left (strafe)
    {
        new_px -= sin(cub->plyr.angle) * cub->plyr.plyr_speed;
        new_py += cos(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == D) // Move right (strafe)
    {
        new_px += sin(cub->plyr.angle) * cub->plyr.plyr_speed;
        new_py -= cos(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == ESC)
        exit(0); // Exit the game

    // Calculate the tiles the player's bounding box intersects
    int tile_x = (int)(new_px / TILE_SIZE);
    int tile_y = (int)(new_py / TILE_SIZE);

    // Check only the tile where the player is moving to
   if (!check_collision(cub, new_px, new_py))
    {
        cub->plyr.px = new_px; // Update position only if there's no collision
        cub->plyr.py = new_py;
    }

    // Re-render the map with the updated player position
    render_map(cub);
    return 0;
}
