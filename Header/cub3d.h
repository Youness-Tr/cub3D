/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:20:39 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/28 12:30:56 by kali             ###   ########.fr       */
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


/*
colors
selver 0xC0C0C0
gray 0x808080
Light Wood: #C19A6B (Light Brown)
Medium Wood: #8B5A2B (Saddle Brown)
Dark Wood: #654321 (Dark Brown)
2. Stone Floor (Earthy, Rugged Feel)
Light Stone: #D3D3D3 (Light Gray)
Medium Stone: #A9A9A9 (Dark Gray)
Dark Stone: #696969 (Dim Gray)
3. Tile Floor (Modern, Sleek Feel)
White Tile: #F5F5F5 (White Smoke)
Gray Tile: #B0C4DE (Light Steel Blue)
Dark Tile: #2F4F4F (Dark Slate Gray)
4. Marble Floor (Luxurious and Elegant)
White Marble: #F8F8FF (Ghost White)
Gray Marble: #BEBEBE (Gray Marble)
Black Marble: #2C2C2C (Black Gray)
5. Rustic Floor (Vintage, Earthy Look)
Terracotta: #E2725B (Warm Earthy Orange)
Clay: #D2691E (Chocolate)
Rust: #8B0000 (Dark Red)
6. Industrial Floor (Concrete, Neutral Look)
Concrete Gray: #808080 (Gray)
Steel Gray: #A9A9A9 (Dark Gray)
Charcoal: #36454F (Charcoal Gray)
*/

#define WIN_H  1900
# define WIN_W  1000
#define TILE_SIZE 40
#define PLAYER_RADIUS (TILE_SIZE / 8)
#define FOV 360
# define PLR 8 // plYER HIGHT WIEGHT
# define ROT_SPEED 0.45
# define P_SPEED 5
# define PI  3.141592653589
# define L_ARROW 65361
#define R_ARROW 65363
#define W  119
#define A 97
#define S 115
#define D 100
#define Q 113
#define R 114
#define ESC 65307


typedef struct s_player //the player structure
{
 int  plyr_x;
 int  plyr_y;
 double angle;
 double fov_rd;
 double  rot; // i think i'll use the macros i don'y need that
 double plyr_speed;
 double px; // remove me later
 double py; // remove me later
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
 int  posx;
 int  posy;
 int  map_w;
 int  map_h;
} t_map;

typedef struct img
{
    void *img;
    char *addr;
    int bpp;
    int len;
    int endian;
    // int h,w;
} t_img;

typedef struct s_mlx //the mlx structure
{
 t_img       img; // the image
//  void       *floor;
//  void       *plyr;
 void       *mlx_w;
 void       *mlxp;
 t_ray      ray;
 t_map      map;
 t_player   plyr;
} t_cub;

int get_win_h(char **av);
void ft_putstr(char *s);
int ft_strcmp(char *ptr1, char *ptr2);
void ft_putstrv2(const char *s, char *str);
char *ft_substr(char *s, unsigned int start, size_t len);
char **ft_split(char *s, char c);
void ft_error(char *s);
char **get_map(char *file);
// void render_map(t_cub *cub);
// void put_ray(t_cub *cub, int len);
void create_img(t_cub *cub);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
void render_map(t_cub *cub);
int mv(int key, t_cub *cub);

#endif