/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:14:56 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/16 16:24:27 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

void ft_errorv2(t_data *data ,char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        write(2,&s[i], 1);
        i++;
    }
    write(2,"\n", 1);
    ft_free(data->map);
    free(data->EA);
    free(data->NO);
    free(data->SO);
    free(data->WE);
    exit(1);
}

void ft_free(char **p)
{
    int i = 0;

    while (p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
}

void ft_error(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        write(2,&s[i], 1);
        i++;
    }
    write(2,"\n", 1);
    exit(1);
}