
# include "Header/cub3d.h"


int is_wall(t_cub *cub,  double x, int y)
{
    // x = floor()
    double px;
    double py;

    px = floor(x / TILE_SIZE);
    py = floor(y / TILE_SIZE);
    // printf("(px, py)(%f, %f)\n", px, py);
    if (px > cub->map.map_w || px < 0 || py < 0 || py > cub->map.map_h)
    {
        printf("Hello\n");
        return (0);
    }
    if (cub->map.map2d[(int)py][(int)px] == '1')
    {
        printf("Hello map == 1\n");
        return (0);
    }
    return (1);
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
            mlx_pixel_put(cub->mlxp, cub->mlx_w, draw_x, draw_y, 0x000000);
        }
        i++;
    }
}

int mv(int key, t_cub *cub)
{
    double x = cub->plyr.plyr_x;
    double y = cub->plyr.plyr_y;

    if (key == W) // Move up
    {
        x += cos(cub->plyr.angle) * P_SPEED;
        y += sin(cub->plyr.angle) * P_SPEED;
    }
    else if (key == S) // Move down
    {
        x -= cos(cub->plyr.angle) * P_SPEED;
        y -= sin(cub->plyr.angle) * P_SPEED;
    }
    else if (key == A) // Move left
    {
        x -= sin(cub->plyr.angle) * P_SPEED;
        y += cos(cub->plyr.angle) * P_SPEED;
    }
    else if (key == D) // Move right
    {
        x += sin(cub->plyr.angle) * P_SPEED;
        y -= cos(cub->plyr.angle) * P_SPEED;
    }
    else if (key == L_ARROW) // Rotate left
        cub->plyr.angle -= cub->plyr.rot * ROT_SPEED;
    else if (key == R_ARROW) // Rotate right
        cub->plyr.angle += cub->plyr.rot * ROT_SPEED;
    else if (key == ESC)
        exit(0);

    if (is_wall(cub, x, y))
    {
        cub->plyr.plyr_x = x;
        cub->plyr.plyr_y = y;
    }

        printf("\t\t\t(%d, %d)\n", (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
    raycaster(cub);
    render_mini_2d(cub);
    put_line(cub, 50, (int)cub->plyr.plyr_x, (int)cub->plyr.plyr_y);
}


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
			if (o->map.map2d[i][j] == 'N')
			{
				o->map.posx = j;
				o->map.posy = i;
				break;
			}
			j++;
		}
		i++;
	}
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;
    // int s_w, s_h;
    // s_w = data->gme->var.s_w;
    // s_h = data->gme->var.s_w;
    // if (x < 0 || x > s_w)
    //     return;
    // if (y > s_h || s_h < 0)
    //     return;
     if (x < 0 || x >= data->gme->var.s_w || y < 0 || y >= data->gme->var.s_h)
        return;
    dst = data->addr + (y * data->len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void init_map(t_cub *cub, char *file)
{
    // cub->map.map2d = get_map(file);
    cub->map.map2d = cub->parse.map;
    if (!cub->map.map2d)
    {
        ft_error("Error: Could not load map");
        exit(1);
    }
    // for(int i = 0; i < 18; i++)
    //     printf("%s", cub->parse.map_cp[i]);
    // exit(0);
    // cub->map.map_h = get_win_h(cub->map.map2d);
    // cub->map.map_w = ft_strlen(cub->map.map2d[0]);
    cub->map.map_h = cub->parse.lines;
    cub->map.map_w = cub->parse.map_len;
    cub->map.posx = cub->parse.player_Y;
    cub->map.posy = cub->parse.player_x;
    // find_plyr_cordn(cub);
    printf("\t(%d, %d)\n",cub->map.posx, cub->map.posy);
}

void init_plyr(t_cub *cub)
{
    cub->plyr.plyr_x = cub->map.posx * TILE_SIZE + TILE_SIZE / 2;
    cub->plyr.plyr_y = cub->map.posy * TILE_SIZE + TILE_SIZE / 2;
    // printf("\t\t(%d, %d)\n",cub->plyr.plyr_x, cub->plyr.plyr_y);
    cub->plyr.angle = 0; //(90 * PI) / 180;
    cub->plyr.rot = 0.1;
    cub->plyr.fov_rd = (FOV * PI) / 180;
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

void init_image(t_cub *cub)
{
    t_img *imge;
    imge = &cub->img;
    imge->gme = cub;
    cub->img.addr = mlx_get_data_addr(imge->img, &imge->bpp, &imge->len, &imge->endian);
}

void render_2d(t_cub *cub)
{
    int i;
    int j;

    j = 0;
    mlx_clear_window(cub->mlxp, cub->mlx_w);
    while (j < cub->map.map_h)
    {
        i = 0;
        while (i < cub->map.map_w)
        {
            if (cub->map.map2d[j][i] == '1')
                render_square(&cub->img, i *TILE_SIZE, j * TILE_SIZE, TILE_SIZE ,0xC0C0C0);
            else if (cub->map.map2d[j][i] == '0' || cub->map.map2d[j][i] == 'P')
            {
                render_square(&cub->img, i *TILE_SIZE , j *TILE_SIZE, TILE_SIZE,0x654321);// 0x8B5A2B
            }
            i++;
        }
        j++;
    }
    // render_square(&cub->img, cub->plyr.plyr_x , cub->plyr.plyr_y, PLAYER_RADIUS,0xFFFFFF);
    render_circle(&cub->img, cub->plyr.plyr_x, cub->plyr.plyr_y, PLAYER_RADIUS,0x000000);
    mlx_clear_window(cub->mlxp, cub->mlx_w);
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}

void render_mini_2d(t_cub *cub)
{
    int i;
    int j;

    j = 0;
    mlx_clear_window(cub->mlxp, cub->mlx_w);
    while (j < cub->map.map_h)
    {
        i = 0;
        while (i < cub->map.map_w)
        {
            if (cub->map.map2d[j][i] == '1')
                render_square(&cub->img, i *TILE_SIZE / 4, j * TILE_SIZE / 4, TILE_SIZE / 4 ,0xC0C0C0);
            else if (cub->map.map2d[j][i] == '0' || cub->map.map2d[j][i] == 'P')
            {
                render_square(&cub->img, i *TILE_SIZE / 4, j *TILE_SIZE / 4, TILE_SIZE / 4,0x654321);// 0x8B5A2B
            }
            i++;
        }
        j++;
    }
    // render_square(&cub->img, cub->plyr.plyr_x , cub->plyr.plyr_y, PLAYER_RADIUS,0xFFFFFF);
    render_circle(&cub->img, cub->plyr.plyr_x/ (TILE_SIZE / 8), cub->plyr.plyr_y/ (TILE_SIZE / 8), PLAYER_RADIUS/2,0x000000);
    mlx_clear_window(cub->mlxp, cub->mlx_w);
    mlx_put_image_to_window(cub->mlxp, cub->mlx_w, cub->img.img, 0, 0);
}


void init_mlx(t_cub *mlx)
{
    int s_w;
    int s_h;

    mlx->var.s_w = mlx->map.map_w * TILE_SIZE;
    mlx->var.s_h = mlx->map.map_h * TILE_SIZE;
    mlx->mlxp = mlx_init();
    mlx->img.img = mlx_new_image(mlx->mlxp,  mlx->var.s_w, mlx->var.s_h);
    mlx->mlx_w = mlx_new_window(mlx->mlxp, mlx->var.s_w, mlx->var.s_h, "Cub3D");
    init_image(mlx);
    // render_2d(mlx);
}

void init_engin(t_cub *cub, char *file)
{
    cub->parse.file_path = file;
    parser(&cub->parse);
    init_map(cub, file); //
    init_plyr(cub);
    init_mlx(cub);
    mlx_hook(cub->mlx_w, 2, 1L<<0, &mv, cub);
    // mlx_loop_hook(cub->mlxp, raycaster, cub);
    mlx_loop(cub->mlxp);
}
int main(int ac, char **av)
{
    t_cub cub;

    if (ac != 2)
        ft_error("Error: ./cub3D Assets/maps/file.cub");
    init_engin(&cub, av[1]);
}