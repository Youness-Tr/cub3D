/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:39:55 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/15 11:43:43 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

int render_map(t_cub *data);

void change_color(char *addr, int w, int h, int color, int size, int bpp)
{
	int x=0, y=0;
	char *px;

	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			px = addr + (y * size + x * (bpp / 8));
			*(int *)px = color;
			x++;
		}
		y++;
	}
}


void put_ray(t_cub *cub, int len)
{
	float deltaX;
	float deltaY;
	int x, y;

	int i;

	i = 0;
	deltaX = cos(cub->ply.angle);
	deltaY = sin(cub->ply.angle);
	while (i < len)
	{
		x = cub->ply.px + i * deltaX;
		y = cub->ply.py + i * deltaY;
		mlx_pixel_put(cub->mlxp, cub->mlx_w, x, y, 0xFF0000);
		i++;
	}
}

int mv(int keycode, t_cub *cub)
{

	mlx_clear_window(cub->mlxp, cub->mlx_w);
	if (keycode == 65361)
	{ // Left arrow key
		printf("Left\n");
		cub->ply.px += cub->ply.dirX * P_SPEED;
		cub->ply.py -= cub->ply.dirY * P_SPEED;
	}
	else if (keycode == 65362)
	{ // Up arrow key
		printf("Up\n");
		cub->ply.px += cub->ply.dirX * P_SPEED;
		cub->ply.py += cub->ply.dirY * P_SPEED;
	}
	else if (keycode == 65363)
	{ // Right arrow key
		printf("Right\n");
		cub->ply.px -= cub->ply.dirX * P_SPEED;
		cub->ply.py += cub->ply.dirY * P_SPEED;
	}
	else if (keycode == 65364)
	{ // Down arrow key
		printf("Down\n");
		cub->ply.px -= cub->ply.dirX * P_SPEED;
		cub->ply.py -= cub->ply.dirY * P_SPEED;
	}
	else if (keycode == 113)// Q
	{
		//rotate to the right
		cub->ply.angle += ROT_SPEED;
		cub->ply.dirX = cos(cub->ply.angle);
		cub->ply.dirY = sin(cub->ply.angle);
	}
	else if (keycode == 115)// S
	{
		//!rotate to the right
		cub->ply.angle -= ROT_SPEED;
		cub->ply.dirX = cos(cub->ply.angle);
		cub->ply.dirY = sin(cub->ply.angle);
	}
	else if (keycode == 65307)
	{ // ESC key
		mlx_destroy_window(cub->mlxp, cub->mlx_w);
        exit(0);
    }
    render_map(cub);
    return (0);
}



// void get_plyr_cordn(t_cub *cub)
// {
//     while
// }
void init_p(t_cub *cub)
{
	cub->ply.angle = PI / 4;
    // get_plyr_cordn(cub);
    cub->ply.dirX = cos(cub->ply.angle);
    cub->ply.dirY = sin(cub->ply.angle);
}
//+++++++++++++++++++++++++++++++++++++
void ft_error(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        write(2,&s[1], 1);
        i++;
    }
    write(2,"\n", 1);
}

char **get_map(char *file)
{
    int fd;
    char *line;
    char *tmp;
    char **map;

    fd = open(file,O_RDONLY);
    if (fd < 0)
        ft_error("Error: map not found");
    tmp = NULL;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break;
        tmp = ft_strjoin(tmp, line);
        free(line);
    }
    map = ft_split(tmp, '\n');
    return (free(tmp), map);
}




void render_wall(t_cub *data, int i, int j)
{
    int bpp;
	int size_len;
	int endian;
	char *addr;

    data->img = mlx_new_image(data->mlxp,50,50);
	addr = mlx_get_data_addr(data->img,&bpp, &size_len, &endian);
	change_color(addr, 50, 50, 0x000000, size_len, bpp);
    mlx_put_image_to_window(data->mlxp, data->mlx_w, data->img, j * TILE_SIZE, i * TILE_SIZE);
	// put_ray(data, 8);
}

void renderSpace(t_cub *data, int i, int j)
{
    int bpp;
	int size_len;
	int endian;
	char *addr;

    data->img = mlx_new_image(data->mlxp,50,50);
	addr = mlx_get_data_addr(data->img,&bpp, &size_len, &endian);
	change_color(addr, 50, 50, 0xFFFFFF, size_len, bpp);
    mlx_put_image_to_window(data->mlxp, data->mlx_w, data->img, j * TILE_SIZE, i * TILE_SIZE);
	// put_ray(data, 8);
}
void renderPlayer(t_cub *data, int i, int j)
{
    int bpp;
	int size_len;
	int endian;
	char *addr;

    data->img = mlx_new_image(data->mlxp,10,10);
	addr = mlx_get_data_addr(data->img,&bpp, &size_len, &endian);
	change_color(addr, 10, 10, 0xFF0001, size_len, bpp);
	mlx_put_image_to_window(data->mlxp, data->mlx_w, data->img, data->ply.px, data->ply.py);

	// put_ray(data, 8);
}

int    render_map(t_cub *data)
{
    int i;
    int j;

    i = 0;
    while (data->map.map2d[i])
    {
        j = 0;
        while (data->map.map2d[i][j])
        {
            if (data->map.map2d[i][j] == '1')
            {
                render_wall(data, i, j);
            }
            else if (data->map.map2d[i][j] == '0')
            {
                renderSpace(data, i,j);
            }
            // else if (data->map.map2d[i][j] == 'P')
            // {
            //     // data->ply.px = j;
            //     // data->ply.py = i;
            //     // renderPlayer(data, i, j);
            // }
            j++;
        }
        i++;
    }
	put_ray(data, 100);
    // renderPlayer(data, data->ply.px / TILE_SIZE, data->ply.py / TILE_SIZE);
    return (0);
}

void data_init(t_cub *data, char *file)
{
    data->map.map2d = get_map(file);
    if (!data->map.map2d)
    {
        ft_error("Error: map not found");
        return;
    }
    init_p(data);
    data->map.map_h = get_win_h(data->map.map2d);
    data->map.map_w = ft_strlen(data->map.map2d[0]);
    data->mlxp = mlx_init();
    data->mlx_w = mlx_new_window(data->mlxp,
             data->map.map_w * TILE_SIZE, data->map.map_h * TILE_SIZE,"cub");
    render_map(data);
}

int main(int ac, char **av)
{
    t_cub data;
    // if (!parsing())//TODO
    // {
    //     ft_error("Error:\n");
    // }
    data_init(&data, av[1]);
	// mlx_loop_hook(data.mlxp, render_map, &data);
    mlx_hook(data.mlx_w,2,1L<<0,&mv, &data);
    mlx_loop(data.mlxp);
}