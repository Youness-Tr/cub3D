/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/19 12:05:56 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

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
				o->plyr.px = j;
				o->plyr.py = i;
				break;
			}
			j++;
		}
		i++;
	}
}

void init_p(t_cub *o)
{
	o->plyr.angle = PI / 4;
	o->plyr.fov_rd = FOV * PI / 180;
	find_plyr_cordn(o);
	// printf("(%f, %f)\n",o->plyr.px, o->plyr.py);
}


void render_map(t_cub *cub)
{
	int i;
	int j;
	int x,y;
	i = 0;
	while (i < cub->map.map_h)
	{
		j = 0;
		while (j < cub->map.map_w)
		{
			if (cub->map.map2d[i][j] == '1')
			{
				cub->img = mlx_xpm_file_to_image(cub->mlxp, "./Assets/walls.xpm",&x, &y);
				mlx_put_image_to_window(cub->mlxp, cub->mlx_w,cub->img, j * TILE_SIZE, i* TILE_SIZE);
			}
			else if (cub->map.map2d[i][j] == '0')
			{
				cub->img = mlx_xpm_file_to_image(cub->mlxp, "./Assets/floor.xpm",&x, &y);
				mlx_put_image_to_window(cub->mlxp, cub->mlx_w,cub->img, j* TILE_SIZE, i* TILE_SIZE);
			}
			j++;
		}
		i++;
	}
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
	cub->mlx_w = mlx_new_window(cub->mlxp, screen_w, screen_h, "Cub3D");
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

//_------------------------------------------------------------------------_
// void change_color(char *addr, int w, int h, int color, int size, int bpp)
// {
// 	int x=0, y=0;
// 	char *px;

// 	while (y < h)
// 	{
// 		x = 0;
// 		while (x < w)
// 		{
// 			px = addr + (y * size + x * (bpp / 8));
// 			*(int *)px = color;
// 			x++;
// 		}
// 		y++;
// 	}
// }


// void put_ray(t_cub *cub, int len)
// {
// 	float deltaX;
// 	float deltaY;
// 	int x, y;

// 	int i;

// 	i = 0;
// 	deltaX = cos(cub->ply.angle);
// 	deltaY = sin(cub->ply.angle);
// 	while (i < len)
// 	{
// 		x = cub->ply.px + i * deltaX;
// 		y = cub->ply.py + i * deltaY;
// 		mlx_pixel_put(cub->mlxp, cub->mlx_w, x, y, 0xFF0001);
// 		i++;
// 	}
// }

// int mv(int keycode, t_cub *cub)
// {


// 	mlx_clear_window(cub->mlxp, cub->mlx_w);
// 	if (keycode == 65361)
// 	{ // Left arrow key
// 		printf("Left\n");
// 		cub->ply.px += cub->ply.dirX * P_SPEED;
// 		cub->ply.py -= cub->ply.dirY * P_SPEED;
// 	}
// 	else if (keycode == 65362)
// 	{ // Up arrow key
// 		printf("Up\n");
// 		cub->ply.px += cub->ply.dirX * P_SPEED;
// 		cub->ply.py += cub->ply.dirY * P_SPEED;
// 	}
// 	else if (keycode == 65363)
// 	{ // Right arrow key
// 		printf("Right\n");
// 		cub->ply.px -= cub->ply.dirX * P_SPEED;
// 		cub->ply.py += cub->ply.dirY * P_SPEED;



// 	}
// 	else if (keycode == 65364)
// 	{ // Down arrow key
// 		printf("Down\n");
// 		cub->ply.px -= cub->ply.dirX * P_SPEED;
// 		cub->ply.py -= cub->ply.dirY * P_SPEED;
// 	}
// 	else if (keycode == 113)// Q
// 	{
// 		//rotate to the right
// 		cub->ply.angle += ROT_SPEED;
// 		cub->ply.dirX = cos(cub->ply.angle);
// 		cub->ply.dirY = sin(cub->ply.angle);
// 	}
// 	else if (keycode == 115)// S
// 	{
// 		//!rotate to the right
// 		cub->ply.angle -= ROT_SPEED;
// 		cub->ply.dirX = cos(cub->ply.angle);
// 		cub->ply.dirY = sin(cub->ply.angle);
// 	}
// 	else if (keycode == 65307)
// 	{ // ESC key
// 		mlx_destroy_window(cub->mlxp, cub->mlx_w);
//         exit(0);
// 	}
// 	put_ray(cub, 100);
// 	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img, cub->ply.px, cub->ply.py);
// 	return (0);
// }


// void init_p(t_cub *cub)
// {
// 	cub->ply.angle = PI / 4;
// 	cub->ply.px = 400;
// 	cub->ply.py = 400;
// 	cub->ply.dirX = cos(cub->ply.angle);
//     cub->ply.dirY = sin(cub->ply.angle);
// }


// int main(int ac, char **av)
// {

// 	t_cub cub;
// 	int bpp;
// 	int size_len;
// 	int endian;
// 	char *addr;

// 	printf("Here\n");
// 	init_p(&cub);
// 	cub.mlxp = mlx_init();
// 	cub.mlx_w = mlx_new_window(cub.mlxp,800, 800, "cub3D");
// 	cub.img = mlx_new_image(cub.mlxp,10,10);
// 	addr = mlx_get_cub_addr(cub.img,&bpp, &size_len, &endian);
// 	change_color(addr, 10, 10, 0xFF0001, size_len, bpp);
// 	put_ray(&cub, 8);
// 	// mlx_key_hook(cub.mlx_w,mv, &cub);
// 	mlx_hook(cub.mlx_w,2,1L<<0,&mv, &cub);
// 	mlx_loop(cub.mlxp);
// }



