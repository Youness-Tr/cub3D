/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/14 17:15:29 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"


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


void put_ray(t_mlx *cub, int len)
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
		mlx_pixel_put(cub->mlxp, cub->mlx_w, x, y, 0xFF0001);
		i++;
	}
}

int mv(int keycode, t_mlx *cub)
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
	put_ray(cub, 100);
	mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img, cub->ply.px, cub->ply.py);
	return (0);
}


void init_p(t_mlx *cub)
{
	cub->ply.angle = PI / 4;
	cub->ply.px = 400;
	cub->ply.py = 400;
	cub->ply.dirX = cos(cub->ply.angle);
    cub->ply.dirY = sin(cub->ply.angle);
}


int main(int ac, char **av)
{

	t_mlx cub;
	int bpp;
	int size_len;
	int endian;
	char *addr;

	printf("Here\n");
	init_p(&cub);
	cub.mlxp = mlx_init();
	cub.mlx_w = mlx_new_window(cub.mlxp,800, 800, "cub3D");
	cub.img = mlx_new_image(cub.mlxp,10,10);
	addr = mlx_get_data_addr(cub.img,&bpp, &size_len, &endian);
	change_color(addr, 10, 10, 0xFF0001, size_len, bpp);
	put_ray(&cub, 8);
	// mlx_key_hook(cub.mlx_w,mv, &cub);
	mlx_hook(cub.mlx_w,2,1L<<0,&mv, &cub);
	mlx_loop(cub.mlxp);
}



