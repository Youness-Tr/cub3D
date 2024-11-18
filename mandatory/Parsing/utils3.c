/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:43:23 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/18 10:39:33 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

int	ft_isdigit(int c)
{
	if ((c < 48 || c > 57))
		return (0);
	else
		return (1);
}

int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == '\n')
		return (1);
	return (0);
}

int	find_direction(t_data *data, char c)
{
	if (c == 'N')
		data->info->plyr.angle = PI / 2;
	else if (c == 'S')
		data->info->plyr.angle = (3 * PI) / 2;
	else if (c == 'W')
		data->info->plyr.angle = PI;
	else if (c == 'E')
		data->info->plyr.angle = 0;
	else
		return (0);
	return (1);
}

void	ft_exit(t_data *data)
{
	ft_free(data->map);
	free(data->ea);
	free(data->no);
	free(data->so);
	free(data->we);
	exit(0);
}

void	ft_free(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}
