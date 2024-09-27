/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/23 15:39:29 by kali             ###   ########.fr       */
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
	o->plyr.px = o->plyr.plyr_x * TILE_SIZE + TILE_SIZE / 2; // we calculate the position in pixels level;
	o->plyr.py = o->plyr.plyr_y * TILE_SIZE + TILE_SIZE / 2;
	printf("(%f, %f)\n", o->plyr.px, o->plyr.py);
}

void init(t_cub *cub, int ac, char **av)
{
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
    create_img(cub);
    render_map(cub);
    mlx_hook(cub->mlx_w, 2, 1L<<0, &mv, cub);
    mlx_loop(cub->mlxp);
}

int main(int ac, char **av)
{
	t_cub cub;

	if (ac < 2 || ac > 2) /*!parsing(av, ac)*/
		ft_error("Error: too many args !!");
	init(&cub, ac, av);
}