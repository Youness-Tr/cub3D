/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:32:43 by kali              #+#    #+#             */
/*   Updated: 2024/09/27 18:10:26 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"


int	is_blocking_down(t_map *map, int new_x, int new_y)
{
	new_x += PLR;
	new_y += PLR;
	new_x /= TILE_SIZE;
	new_y /= TILE_SIZE;
	if (new_x < 0 || new_x >= map->map_w || new_y < 0 ||
		new_y >= map->map_h)
	{
		return (1);
	}
	if (map->map2d[new_y][new_x] == '1')
		return (1);
	return (0);
}

int	is_blocking_up(t_map *map, int new_x, int new_y)
{
	new_x -= PLR;
	new_y -= PLR;
	new_x /= TILE_SIZE;
	new_y /= TILE_SIZE;
	if (new_x < 0 || new_x >= map->map_w || new_y < 0 ||
		new_y >= map->map_h)
	{
		return (1);
	}
	if (map->map2d[new_y][new_x] == '1')
		return (1);
	return (0);
}

int	is_blocking_right(t_map *map, int new_x, int new_y)
{
	new_x += PLR;
	new_y -= PLR;
	new_x /= TILE_SIZE;
	new_y /= TILE_SIZE;
	if (new_x < 0 || new_x >= map->map_w || new_y < 0 ||
		new_y >= map->map_h)
	{
		return (1);
	}
	if (map->map2d[new_y][new_x] == '1')
		return (1);
	return (0);
}

int	is_blocking_left(t_map *map, int new_x, int new_y)
{
	new_x -= PLR;
	new_y += PLR;
    new_x /= TILE_SIZE;
    new_y /= TILE_SIZE;
    if (new_x < 0 || new_x >= map->map_w || new_y < 0 || new_y >= map->map_h)
	{
		return (1);
	}
	if (map->map2d[new_y][new_x] == '1')
		return (1);
	return (0);
}


static int	is_blocking(t_map *map, int new_x, int new_y)
{
	if (is_blocking_up(map, new_x, new_y))
		return (1);
	if (is_blocking_down(map, new_x, new_y))
		return (1);
	if (is_blocking_right(map, new_x, new_y))
		return (1);
	if (is_blocking_left(map, new_x, new_y))
		return (1);
	return (0);
}

void put_line(t_cub *cub, int len, int x, int y)
{
    float deltaX;
    float deltaY;
    float incngl; // increment angle;

    int i = 0;
    cub->ray.ray_ngl = cub->plyr.fov_rd / 2;
    incngl = cub->plyr.fov_rd / 2;
    incngl = incngl / cub->map.map_w * TILE_SIZE;
    deltaX = cos(cub->plyr.angle);
    deltaY = sin(cub->plyr.angle);

    while (i < len)
    {
        int draw_x = x + i * deltaX;
        int draw_y = y + i * deltaY;

        // Draw only if within window bounds
        if (draw_x >= 0 && draw_x < TILE_SIZE * cub->map.map_w &&
            draw_y >= 0 && draw_y < TILE_SIZE * cub->map.map_h)
        {
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, 0x000000);
        }
        i++;
    }
}

#define NUM_RAYS 10
#define FOV_ANGLE (60.0 * (PI / 180.0)) // Convert to radians
#define ANGLE_INCREMENT (FOV_ANGLE / NUM_RAYS) // Angle increment per ray
void draw_line(t_cub *cub, int start_x, int start_y, int end_x, int end_y, int color) {
    float deltaX = end_x - start_x;
    float deltaY = end_y - start_y;
    float step = fmax(fabs(deltaX), fabs(deltaY)); // Maximum steps to ensure line is drawn correctly

    deltaX /= step;
    deltaY /= step;

    for (int i = 0; i <= step; i++) {
        int draw_x = (int)(start_x + i * deltaX);
        int draw_y = (int)(start_y + i * deltaY);

        // Draw only if within window bounds
        if (draw_x >= 0 && draw_x < TILE_SIZE * cub->map.map_w &&
            draw_y >= 0 && draw_y < TILE_SIZE * cub->map.map_h) {
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, color);
        }
    }
}


void cast_rays(t_cub *cub) {
    double ray_angle;
    double next_horizontal_x, next_horizontal_y;
    double next_vertical_x, next_vertical_y;
    double step_x, step_y;

    // Calculate the angle increment for each ray based on the field of view
    double angle_increment = cub->plyr.fov_rd / NUM_RAYS;

    for (int ray_index = 0; ray_index < NUM_RAYS; ray_index++) {
        // Calculate the ray angle
        ray_angle = cub->plyr.angle - (cub->plyr.fov_rd / 2) + (ray_index * angle_increment);

        // Cast horizontal ray
        next_horizontal_x = cub->plyr.px;
        next_horizontal_y = cub->plyr.py;

        // Calculate horizontal step sizes
        step_x = cos(ray_angle) * TILE_SIZE;
        step_y = sin(ray_angle) * TILE_SIZE;

        // Cast horizontal ray
        while (1) {
            // Calculate grid position
            int hx = (int)(next_horizontal_y / TILE_SIZE);
            int wx = (int)(next_horizontal_x / TILE_SIZE);

            // Check bounds for horizontal ray
            if (hx >= 0 && hx < cub->map.map_h && wx >= 0 && wx < cub->map.map_w) {
                if (cub->map.map2d[hx][wx] == '1') { // Hit a wall
                    cub->ray.distance = hypot(next_horizontal_x - cub->plyr.px, next_horizontal_y - cub->plyr.py);
                    cub->ray.flag = 1; // Wall hit
                    printf("Hit horizontal wall at (%d, %d)\n", hx, wx);

                    // Render the ray line as a black line
                    draw_line(cub, (int)cub->plyr.px, (int)cub->plyr.py, (int)next_horizontal_x, (int)next_horizontal_y, 0x000000);
                    break;
                }
            } else {
                break; // Out of bounds
            }

            // Move to the next horizontal grid line
            next_horizontal_x += step_x;
            next_horizontal_y += step_y;
        }

        // Cast vertical ray
        next_vertical_x = cub->plyr.px;
        next_vertical_y = cub->plyr.py;

        // Calculate vertical step sizes
        step_x = TILE_SIZE; // Fixed step size for vertical rays
        step_y = 0;

        // Cast vertical ray
        while (1) {
            // Calculate grid position
            int vy = (int)(next_vertical_y / TILE_SIZE);
            int vx = (int)(next_vertical_x / TILE_SIZE);

            // Check bounds for vertical ray
            if (vy >= 0 && vy < cub->map.map_h && vx >= 0 && vx < cub->map.map_w) {
                if (cub->map.map2d[vy][vx] == '1') { // Hit a wall
                    cub->ray.distance = hypot(next_vertical_x - cub->plyr.px, next_vertical_y - cub->plyr.py);
                    cub->ray.flag = 1; // Wall hit
                    printf("Hit vertical wall at (%d, %d)\n", vy, vx);

                    // Render the ray line as a black line
                    draw_line(cub, (int)cub->plyr.px, (int)cub->plyr.py, (int)next_vertical_x, (int)next_vertical_y, 0x000000);
                    break;
                }
            } else {
                break; // Out of bounds
            }

            // Move to the next vertical grid line
            next_vertical_x += step_x;
            next_vertical_y += step_y;
        }
    }
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
   if (!is_blocking(&cub->map, new_px, new_py))
    {
        cub->plyr.px = new_px; // Update position only if there's no collision
        cub->plyr.py = new_py;
    }

    // Re-render the map with the updated player position
    render_map(cub);
    put_line(cub, 500, (int)cub->plyr.px, (int)cub->plyr.py);
    cast_rays(cub);
    return 0;
}
