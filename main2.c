/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 14:28:18 by kali              #+#    #+#             */
/*   Updated: 2024/09/27 15:43:01 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

void drow_elements(t_cub *cub, int x, int y, int color, int size);
void find_plyr_cordn(t_cub *o)
{
	int i;
	int j;

	i = 0;
	while (i < o->map.map_h)
	{
		j = 0;
		while (j < o->map.map_w)
		{
			if (o->map.map2d[i][j] == 'P')
			{
				o->plyr.plyr_x = j;
				o->plyr.plyr_y = i;
				break;
			}
			j++;
		}
		i++;
	}
}

void init_p(t_cub *o)
{
	o->plyr.angle = PI / 2;
	o->plyr.rot = 0.1;
	o->plyr.plyr_speed = P_SPEED;
	o->plyr.fov_rd = FOV * PI / 180;
	find_plyr_cordn(o);
	o->plyr.px = o->plyr.plyr_x * TILE_SIZE ; // we calculate the position in pixels level;
	o->plyr.py = o->plyr.plyr_y * TILE_SIZE;
	printf("(%f, %f)\n", o->plyr.px, o->plyr.py);
}


#define MAX_RAYS 60 // Number of rays to cast
#define DISTANCE_LIMIT 1000 // Maximum distance to cast rays



int is_collision_with_wall(t_cub *cub, int player_x, int player_y)
{
    // Check surrounding pixels of the player
    for (int i = 0; i < TILE_SIZE / 2; i++)
    {
        for (int j = 0; j < TILE_SIZE / 2; j++)
        {
            // Calculate the pixel position
            int check_x = player_x + i;
            int check_y = player_y + j;

            // Ensure the coordinates are within bounds
            if (check_x < 0 || check_y < 0 || check_x >= (TILE_SIZE * cub->map.map_w) || check_y >= (TILE_SIZE * cub->map.map_h))
                return 1; // Treat out of bounds as a collision

            // Get the color of the pixel
            char *dst = cub->img.addr + (check_y * cub->img.len + check_x * (cub->img.bpp / 8));
            unsigned int color = *(unsigned int *)dst;

            // Define the wall color (brown in this case)
            unsigned int wall_color = 0x964B00;

            // Check if the player's pixel is touching a wall pixel
            if (color == wall_color)
                return 1; // Collision detected
        }
    }
    return 0; // No collision
}

void put_line(t_cub *cub, int len, int x, int y)
{
    float deltaX;
    float deltaY;

    int i = 0;
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
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, 0xFF00FF);
        }
        i++;
    }
}

void cast_rays(t_cub *cub)
{
    float ray_angle;
    float angle_step;
    int ray_count = MAX_RAYS;
    float ray_dir_x;
    float ray_dir_y;

    // Calculate the angle increment per ray
    angle_step = cub->plyr.fov_rd / ray_count;
    ray_angle = cub->plyr.angle - (cub->plyr.fov_rd / 2);

    for (int i = 0; i < ray_count; i++)
    {
        // Calculate the ray direction using cosine and sine
        ray_dir_x = cos(ray_angle);
        ray_dir_y = sin(ray_angle);

        float current_x = cub->plyr.px;
        float current_y = cub->plyr.py;

        float step_x = (ray_dir_x > 0) ? TILE_SIZE : -TILE_SIZE;
        float step_y = (ray_dir_y > 0) ? TILE_SIZE : -TILE_SIZE;

        float delta_x = step_x * fabs(ray_dir_y / ray_dir_x);
        float delta_y = step_y * fabs(ray_dir_x / ray_dir_y);

        int hit = 0;
        float distance = 0;

        // DDA Loop
        while (!hit && distance < DISTANCE_LIMIT)
        {
            // Move to the next grid cell
            if (fabs(current_x - cub->plyr.px) < fabs(current_y - cub->plyr.py))
            {
                current_x += step_x;
                current_y += ray_dir_y * (step_x / ray_dir_x);
            }
            else
            {
                current_y += step_y;
                current_x += ray_dir_x * (step_y / ray_dir_y);
            }

            // Check for collision
            if (is_collision_with_wall(cub, (int)current_x, (int)current_y))
            {
                hit = 1;
                put_line(cub, distance, cub->plyr.px, cub->plyr.py);
            }

            // Increment distance
            distance += sqrt(delta_x * delta_x + delta_y * delta_y);
        }

        // Move to the next ray angle
        ray_angle += angle_step;
    }
}




void put_ray(t_cub *cub, int len)
{
	float deltaX;
	float deltaY;
	int x, y;

	int i;

	i = 0;
	deltaX = cos(cub->plyr.angle);
	deltaY = sin(cub->plyr.angle);
	while (i < len)
	{
		x = (cub->plyr.px + i * deltaX) + TILE_SIZE / 2;
		y = (cub->plyr.py + i * deltaY) + TILE_SIZE / 2;
		mlx_pixel_put(cub->mlxp, cub->mlx_w, x, y, 0xFF00FF);
		i++;
	}
}

void mv_player(t_cub *cub, float target_x, float target_y)
{
    // Move the player to the target position in pixels
    cub->plyr.px = target_x;
    cub->plyr.py = target_y;

    // Update the player's map position
    cub->plyr.plyr_x = (int)(cub->plyr.px / TILE_SIZE);
    cub->plyr.plyr_y = (int)(cub->plyr.py / TILE_SIZE);
}

int mv(int key, t_cub *cub)
{
    float target_x = cub->plyr.px;
    float target_y = cub->plyr.py;
	if (key == R_ARROW)
		cub->plyr.angle += cub->plyr.rot * ROT_SPEED;
    else if (key == Q)
        cub->plyr.plyr_speed += 5;
    else if (key == R)
        cub->plyr.plyr_speed -= 5;
    else if (key == L_ARROW)
        cub->plyr.angle -= cub->plyr.rot * ROT_SPEED;
	else if (key == W) // Move forward
    {
        target_x += cos(cub->plyr.angle) * cub->plyr.plyr_speed;
        target_y += sin(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == S) // Move backward
    {
        target_x -= cos(cub->plyr.angle) * cub->plyr.plyr_speed;
        target_y -= sin(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == A) // Move left
    {
        target_x -= sin(cub->plyr.angle) * cub->plyr.plyr_speed;
        target_y += cos(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
    else if (key == D) // Move right
    {
        target_x += sin(cub->plyr.angle) * cub->plyr.plyr_speed;
        target_y -= cos(cub->plyr.angle) * cub->plyr.plyr_speed;
    }
	else if (key == ESC)
		exit(0); // free memory
	printf("(%f, %f)\n", (target_x / TILE_SIZE), (target_x / TILE_SIZE));
	if (!is_collision_with_wall(cub, (int)(target_x),  (int)(target_y)))
	{
        // Update player position
        mv_player(cub, target_x, target_y);
    }
	else
		printf("_______________________OHOY_________________________\n");

	render_map(cub);
    cast_rays(cub);
    put_ray(cub, 1001);
    return 0;
}
void render_minimap(t_cub *cub)
{
    int minimap_x = 10; // X position on the screen
    int minimap_y = 10; // Y position on the screen
    int minimap_scale = 0.2; // Scale for minimap tiles (20% of original size)

    for (int i = 0; i < cub->map.map_h; i++)
    {
        for (int j = 0; j < cub->map.map_w; j++)
        {
            int color;

            if (cub->map.map2d[i][j] == '1')
                color = 0x964B00; // Wall color
            else if (cub->map.map2d[i][j] == '0')
                color = 0xFFFFFF; // Empty space color
            else if (cub->map.map2d[i][j] == 'P')
                color = 0x0000FF; // Player color

            // Draw the scaled tile
            drow_elements(cub, minimap_x + j * TILE_SIZE * minimap_scale,
                          minimap_y + i * TILE_SIZE * minimap_scale,
                          color, TILE_SIZE * minimap_scale);
        }
    }

    // Optionally, draw the player position on the minimap
    int player_size = TILE_SIZE * minimap_scale;
    int player_x = minimap_x + (cub->plyr.plyr_x * TILE_SIZE * minimap_scale) + (player_size / 4);
    int player_y = minimap_y + (cub->plyr.plyr_y * TILE_SIZE * minimap_scale) + (player_size / 4);
    drow_elements(cub, player_x, player_y, 0xFF0000, player_size / 2); // Draw player in red
}


void modf_img(t_cub *cub, int x, int y, int color)
{
    char *dst;

    if (x < 0 || y < 0 || x >= (TILE_SIZE * cub->map.map_w) || y >= (TILE_SIZE * cub->map.map_h))
        return;

    dst = cub->img.addr + (y * cub->img.len + x * (cub->img.bpp / 8));
    *(unsigned int *)dst = color;
}

void ft_create_imgs(t_cub *cub)
{
    cub->img.img = mlx_new_image(cub->mlxp, TILE_SIZE * cub->map.map_w, TILE_SIZE * cub->map.map_h);
    cub->img.addr = mlx_get_data_addr(cub->img.img, &cub->img.bpp, &cub->img.len, &cub->img.endian);
}

void drow_elements(t_cub *cub, int x, int y, int color, int size)
{
    int i;
    int j;

    i = 0;
    while (i < size)
    {
        j = 0;
        while (j < size)
        {
            modf_img(cub, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

static void	put_mini_player(t_cub *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			ft_mlx_pixel_put(data, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void render_map(t_cub *cub)
{
    int i, j;

    for (i = 0; i < cub->map.map_h; i++)
    {
        for (j = 0; j < cub->map.map_w; j++)
        {
            if (cub->map.map2d[i][j] == '1')
            {
                drow_elements(cub, j * TILE_SIZE, i * TILE_SIZE, 0x964B00, TILE_SIZE);
            }
            else if (cub->map.map2d[i][j] == '0' || cub->map.map2d[i][j] == 'P')
            {
                drow_elements(cub, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF, TILE_SIZE);
            }
        }
    }

    // Render player as floating
    put_mini_player(cub, cub->plyr.plyr_x, cub->plyr.plyr_y, 0x000000);
    // int player_size = TILE_SIZE/ 8;
    // int x_offset = (TILE_SIZE - player_size) / 2;
    // int y_offset = (TILE_SIZE - player_size) / 2 - TILE_SIZE / 8;
    // drow_elements(cub, (int)cub->plyr.px * TILE_SIZE, (int)cub->plyr.py * TILE_SIZE, 0xFFFFFF, TILE_SIZE);
    // render_minimap(cub);
    // drow_elements(cub, (int)cub->plyr.px + x_offset, (int)cub->plyr.py + y_offset, 0x000000, player_size);
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}

void init(t_cub *cub, int ac, char **av)
{
	/*init map*/
	int screen_w;
	int screen_h;
	cub->map.map2d = get_map(av[1]);
	if (!cub->map.map2d)
		ft_error("Error: map not found");
	cub->map.map_h = get_win_h(cub->map.map2d);
    cub->map.map_w = ft_strlen(cub->map.map2d[0]);
	init_p(cub);
	screen_w = TILE_SIZE * cub->map.map_w;
	screen_h = TILE_SIZE * cub->map.map_h;
	cub->mlxp = mlx_init();
	ft_create_imgs(cub);//tmp function for learning
	cub->mlx_w = mlx_new_window(cub->mlxp, screen_w, screen_h, "Cub3D");
	mlx_hook(cub->mlx_w, 2, 1L<<0, &mv, cub);
	render_map(cub);
	mlx_loop(cub->mlxp);
}

int main(int ac, char **av)
{
	t_cub cub;

	if (ac < 2 || ac > 2) /*!parsing(av, ac)*/
		ft_error("Error: too many args !!");
	init(&cub, ac, av);
}
