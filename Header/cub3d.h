/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:20:39 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/01 18:33:25 by kali             ###   ########.fr       */
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



# define WIN_W 1920
#define WIN_H  1080
#define TILE_SIZE 64
#define MINI_MAP 0.25
#define PLAYER_RADIUS (TILE_SIZE / 10)
# define PLR 8 // plYER HIGHT WIEGHT (remove this)
#define NRAYS 540
#define ROT_SPEED 0.03
# define P_SPEED 5
# define PI  3.141592653589
#define FOV  (84 * PI)/180
# define L_ARROW 65361
#define R_ARROW 65363
#define W  119
#define A 97
#define S 115
#define D 100
#define Q 113//*REMOVE
#define R 114//*REMOVE
#define ESC 65307

/****************TxTColoR*******************/
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"
#define RES     "\033[0m"
/****************TxTColoR*******************/
typedef struct s_mlx t_cub;
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
 int  hit;  // flag for the wall
 double hit_x;
 double hit_y;
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
    t_cub *gme;
    int h;
    int w;
} t_img;
// this struct is for variable for norms or any shared variable
typedef struct vars
{
    int s_w; // screen wigth
    int s_h; // screen wieght

} t_vars;
/******************/
typedef struct s_data
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    int F;
    int C;
    char **map;
    char *file_path; //
    int fd;
    int player_x;
    int player_Y;
    int map_w;
    int lines;
    int stop;
    int len;
    int map_len;
    t_cub *info;
} t_data;
/***************************/


typedef struct s_leak
{
	void			*address;
	struct s_leak	*next;
}					t_leak;

struct s_mlx //the mlx structure
{
 t_img       img;
 void       *mlx_w;
 void       *mlxp;
 t_ray      ray;
 t_map      map;
 t_player   plyr;
 t_data     parse;
 t_vars     var;
 t_img      textures[4];
 t_leak     *free;
 int move_forward;
 int move_backward;
 int move_left;
 int move_right;
 int rotate_left;
 int rotate_right;
};


int get_win_h(char **av);
void ft_putstr(char *s);
void ft_putstrv2(const char *s, char *str);
char *ft_substr(char *s, unsigned int start, size_t len);
char **ft_split(char *s, char c);
void ft_error(char *s);
char **get_map(char *file);
void my_mlx_pixel_put(t_img *data, int x, int y, int color);
int raycaster(t_cub *cub);
void put_line(t_cub *cub, int len, int x, int y);
int parser(t_data *data);
int is_valid_char(char c);
void init(t_data *data);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int count_len(t_data *data);
void ft_error(char *str);
void render_2d(t_cub *cub);
void render_mini_2d(t_cub *cub);
void ft_renderThreeD(t_cub *cub, double distnce, int raypt, int tex_x);

//Glogic > playerMoves.c:
int mv(int key, t_cub *cub);
//Glogic > Wall_intersection.c:
int is_wall(t_cub *cub, double x, int y);
// Glogic/
double angle_range(double ngl);

// int is_valid_char(char c);
int	create_trgb(int t, int r, int g, int b);
int	ft_atoi(const char *nptr);
char	*ft_itoa(int n);
int main_loop(t_cub *cub);
int key_release(int key, t_cub *cub);
int key_press(int key, t_cub *cub);
// int count_len(t_data *data);
void put_rays(t_cub *cub, int len, int x, int y, float ngl);
// int	ft_strcmp(const char *s1, const char *s2);
// char	*ft_strnstr(const char *big, const char *little, size_t len);

// INIT :
void init_engin(t_cub *cub, char *file);
void init_plyr(t_cub *cub);
void init_map(t_cub *cub, char *file);
//Rendering
t_img* get_texture(t_cub *cub, int flag);

//Leaks:
void	*ft_malloc(t_cub *cub, size_t size);

#endif
