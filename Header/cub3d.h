/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:20:39 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/04 15:28:15 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "get_next_line.h"



typedef struct s_data 
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char *F;
    char *C;
    char **array;
    char **map;
    char **map_cp;
    char *file_path;
    int fd;
    int player_x;
    int player_Y;
    int space;
    int faragh;
    int lines;
    int stop;
    int len;
    char *test;
} t_data;

// parsing //

char	*ft_substr(char *s, unsigned int start, size_t len);
void	floodfill_check(t_data *data);
void count_spaces(t_data *data);
int parser(t_data *data);

// parsing utils //
char	*ft_substr(char *s, unsigned int start, size_t len);
int is_valid_char(char c);
void init(t_data *data);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int count_len(t_data *data);
void ft_error(char *str);


#endif