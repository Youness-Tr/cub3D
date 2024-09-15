/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:20:39 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/15 10:31:08 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
// # include <mlx.h>
#include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"

#define WIN_H  1900
# define WIN_W  1000
#define TILE_SIZE 32
#define FOV 60
# define ROT_SPEED 0.045
# define P_SPEED 15
# define PI  3.141592653589

typedef struct s_player //the player structure
{
 int  plyr_x; // player x position in pixels
 int  plyr_y; // player y position in pixels
 double angle; // player angle
 float fov_rd; // field of view in radians
 int  rot; // rotation flag
 double dirX;
 double dirY;
 double px;
 double py;
} t_player;

typedef struct s_ray //the ray structure
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 int  flag;  // flag for the wall
} t_ray;

typedef struct s_map //the data structure
{
 char **map2d;
 int  p_x;
 int  p_y;
 int  map_w;
 int  map_h;
} t_map;

typedef struct s_mlx //the mlx structure
{
 void       *img; // the image
 void       *mlx_w;
 void       *mlxp;
 t_ray      ray;
 t_map      map;
 t_player   ply;
} t_cub;

int get_win_h(char **av);
void ft_putstr(char *s);
int ft_strcmp(char *ptr1, char *ptr2);
void ft_putstrv2(const char *s, char *str);
char *ft_substr(char *s, unsigned int start, size_t len);
char **ft_split(char *s, char c);

#endif