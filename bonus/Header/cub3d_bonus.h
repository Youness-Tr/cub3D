/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:58:58 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/16 10:28:28 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../../Gnl/get_next_line.h"
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIN_W 1000
# define WIN_H 920
# define TILE_SIZE 32
# define PLAYER_RADIUS 16
# define PLAYER_RANGE 500
# define MINI_TILE 8
# define MINI_MAP 0.25
# define ROT_SPEED 0.01
# define P_SPEED 2
# define PI 3.14159265358979323846
# define FOV 60
# define DOOR_OPEN_DISTANCE 1.5
# define MAX_DOOR 20
# define MAX_TEXTURES 5
# define MAX_GUN 19
# define ZOOM_TEXTURE 4
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307
# define L_ARROW 65361
# define R_ARROW 65363
# define E 32

# define L_MOUS 1
# define R_MOUS 3

typedef struct s_mlx	t_cub;
typedef struct s_player
{
	double				plyr_x;
	double				plyr_y;
	double				angle;
	double				fov_rd;
}						t_player;

typedef struct s_ray
{
	double				ray_ngl;
	double				distance;
	int					hit;
	double				hit_x;
	double				hit_y;
	int					hit_door;
}						t_ray;

typedef struct s_map
{
	char				**map2d;
	int					posx;
	int					posy;
	int					map_w;
	int					map_h;
}						t_map;

typedef struct img
{
	void				*img;
	char				*addr;
	int					bpp;
	int					len;
	int					endian;
	t_cub				*gme;
	int					h;
	int					w;
}						t_img;

typedef struct vars
{
	int					s_w;
	int					s_h;
	double				hx;
	double				hy;
	double				vx;
	double				vy;
	double				y_step;
	double				x_step;
	int					pxl;
	double				h_inter;
	double				v_inter;
	double				wall_x;
	int					tex_x;
	int					nray;
	double				ngl;
	double				new_x;
	double				new_y;
	int					toppxl;
	int					lowpxl;
	bool				shoot;
	int					x;
	int					y;
	int					map_x;
	int					map_y;
	int					start_x;
	int					end_x;
	int					start_y;
	int					end_y;
	int					render_x;
	int					render_y;

}						t_vars;

typedef struct s_data
{
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	int					f;
	int					c;
	char				**map;
	char				*file_path;
	int					fd;
	int					player_x;
	int					player_y;
	int					map_w;
	int					lines;
	int					stop;
	int					len;
	int					map_len;
	t_cub				*info;
}						t_data;

typedef struct s_leak
{
	void				*address;
	struct s_leak		*next;
}						t_leak;

typedef struct s_door
{
	int					x;
	int					y;
	int					open;
	int					frame;
	double				distance;
}						t_door;

struct					s_mlx
{
	t_img				img;
	void				*mlx_w;
	void				*mlxp;
	t_ray				ray;
	t_map				map;
	t_player			plyr;
	t_data				parse;
	t_vars				var;
	t_img				textures[5];
	t_img				gun[19];
	t_img				door[22];
	t_leak				*free;
	int					move_forward;
	int					move_backward;
	int					move_left;
	int					move_right;
	int					rotate_left;
	int					rotate_right;
	int					gun_frame;
	int					is_shooting;
	t_door				*doors;
	t_door				default_door;
	int					ndoors;
	int					mv;
};

void					ft_putstr(char *s);
void					ft_putstrv2(const char *s, char *str);
char					*ft_substr(char *s, unsigned int start, size_t len);
char					**ft_split(char *s, char c);
void					ft_error(char *s);
void					ft_errorv2(t_data *data, char *s);
void					ft_exit(t_data *data);
char					**get_map(char *file);
void					*get_value(char *s, unsigned int start, t_cub *cub);
int						get_haxe(char *s, unsigned int start, t_cub *cub);
void					ft_init(char *line, t_data *data);
int						space_skip(char *s);
int						find_direction(t_data *data, char c);
int						ft_isdigit(int c);
void					door_checking(t_data *data, int i, int j);
char					*join_space(char *s1, char *s2, t_cub *cub);
void					my_mlx_pixel_put(t_img *data, int x, int y, int color);
int						raycaster(t_cub *cub);
void					put_line(t_cub *cub, int len, int x, int y);
int						parser(t_data *data);
int						is_valid_char(char c);
void					init(t_data *data);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strnstr(const char *big, const char *little,
							size_t len);
int						count_len(t_data *data);
void					render_mini_2d(t_cub *cub);
void					render_three_d(t_cub *cub, double distnce, int raypt,
							int tex_x);
int						_close_window(t_cub *cub);
// Glogic > playerMoves.c:
int						mv(int key, t_cub *cub);
// Glogic > Wall_intersection.c:
int						is_wall(t_cub *cub, double x, double y);
// Glogic/
double					angle_range(double ngl);
void					shoot(t_cub *cub);
void					count_door_distances(t_cub *cub);
void					render_weapon(t_cub *cub);
void					handle_door_interaction(t_cub *cub, int i);
// void					set_gun(t_cub *cub, char *file);
int						key_press(int key, t_cub *cub);
int						key_release(int key, t_cub *cub);
int						mouse_press(int button, int x, int y, t_cub *cub);
int						mouse_release(int button, int x, int y, t_cub *cub);
int						mouse_mv(int btn, int x, int y, t_cub *cub);

// int is_valid_char(char c);
int						create_trgb(int t, int r, int g, int b);
int						ft_atoi(const char *nptr);
char					*ft_itoa(int n);
int						main_loop(t_cub *cub);
int						key_release(int key, t_cub *cub);
int						key_press(int key, t_cub *cub);

// INIT :
void					init_engin(t_cub *cub, char *file);
void					init_plyr(t_cub *cub);
void					init_map(t_cub *cub);
void					load_texture(t_cub *cub, t_img *texture,
							char *file_path);
void					init_textures(t_cub *cub);
void					get_doors_cordn(t_cub *o);
void					ndoors(t_cub *o);
// Rendering
t_img					*get_texture(t_cub *cub, int flag);
// void					put_line(t_cub *cub, int len, int x, int y);
void					my_mlx_pixel_put(t_img *data, int x, int y, int color);
void					draw_floor_ceiling(t_cub *cub, int raypt, int toppxl,
							int lowpxl);
double					calculate_wall_x(t_ray *ray);
int						get_texture_x(t_cub *cub, double wall_x);
int						wall_hit(float x, float y, t_cub *mlx);

// Leaks:
void					*ft_malloc(t_cub *cub, size_t size);
void					ft_free_all(t_leak *cub);
char					*ft_strdupv2(char *s1, t_cub *leak);
char					*ft_strjoinv2(char *s1, char *s2, t_cub *cub);
char					*ft_substrv2(char *s, unsigned int start, size_t len,
							t_cub *cub);
char					**ft_splitv2(char *s, char c, t_cub *cub);

// RayCasting
double					distance(t_cub *cub, double x, double y);

// Events
int						mouse_press(int button, int x, int y, t_cub *cub);
int						mouse_release(int button, int x, int y, t_cub *cub);
int						mouse_mv(int btn, int x, int y, t_cub *cub);
void					render_minimap(t_cub *cub);

#endif
