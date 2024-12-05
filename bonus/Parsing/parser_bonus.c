/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/05 18:32:30 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

int	ft_check(t_data *data)
{
	int	i;
	int	j;
	int	ply;

	i = -1;
	ply = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (find_direction(data, data->map[i][j]))
			{
				data->player_x = i;
				data->player_y = j;
				ply++;
			}
			if (!is_valid_char(data->map[i][j]))
				return (1);
		}
	}
	if (ply > 1 || ply == 0)
		return (1);
	data->lines = i - 1;
	return (0);
}

void	add_to_map(t_data *data)
{
	int	i;

	data->map_w = 0;
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) > data->map_w)
			data->map_w = ft_strlen(data->map[i]);
		i++;
	}
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) < data->map_w)
		{
			while (ft_strlen(data->map[i]) < data->map_w)
				data->map[i] = join_space(data->map[i], " ", data->info);
			data->map[i] = ft_strjoinv2(data->map[i], "\n", data->info);
		}
		i++;
	}
	data->map_len = data->map_w;
}

void	map_fill(t_data *data)
{
	int		j;
	char	*line;
	int		fd;

	j = 0;
	fd = open(data->file_path, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!data->stop)
			ft_init(line, data);
		if (data->stop)
		{
			data->map[j] = ft_strdupv2(line, data->info);
			j++;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!data->stop)
		ft_errorv2(data, "Error\n:: MAP DOSEN'T EXIST");
	data->map[j] = NULL;
	close(fd);
}

void	map_scan(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i <= data->lines)
	{
		j = -1;
		while (++j < data->map_w)
		{
			if (data->map[i][j] == '0' || data->map[i][j] == 'N'
				|| data->map[i][j] == 'S' || data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'D')
			{
				if (i == 0 || i == data->lines || j == 0 || j == data->map_w
					- 2)
					ft_errorv2(data, "Error\n:: INVALID MAP"); 
				if (data->map[i - 1][j] == ' ' || data->map[(i) + 1][j] == ' '
					|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
					ft_errorv2(data, "Error\n:: INVALID MAP");
			}
			if (data->map[i][j] == 'D')
				door_checking(data, i, j);
		}
	}
}

int	parser(t_data *data)
{
	init(data);
	map_fill(data);
	if (ft_check(data))
		ft_errorv2(data, "Error\n:: MAP ELEMENT");
	add_to_map(data);
	map_scan(data);
	return (0);
}
