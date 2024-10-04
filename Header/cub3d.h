/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 10:20:39 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/02 19:01:56 by ytarhoua         ###   ########.fr       */
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
    int player_x;
    int player_Y;
    int space;
    int faragh;
    int lines;
    int stop;
    char *test;
} t_data;


char	*ft_substr(char *s, unsigned int start, size_t len);
void	floodfill_check(t_data *data);
void count_spaces(t_data *data);


#endif