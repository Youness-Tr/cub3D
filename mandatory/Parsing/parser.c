/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/18 10:21:02 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

int	ft_check(t_data *data)
{
	int	i;
	int	j;
	int ply;

	i = 0;
	ply = 0;
	while (data->map[i])
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
		i++;
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
	//*DONE :i need to check here for load textures and colors;
	if (!data->stop)
	{
		ft_errorv2(data, "Error");
	}
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
				|| data->map[i][j] == 'E')
			{
				if (i == 0 || i == data->lines || j == 0 || j == data->map_w
					- 2)
				{
					printf("i ::%i && j ::%i", data->lines, data->map_w);
					ft_errorv2(data, "error::::: invalid map");
				}
				if (data->map[i - 1][j] == ' ' || data->map[(i) + 1][j] == ' '
					|| data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
					ft_errorv2(data, "error::::: invalid map");
			}
		}
	}
}

void print_leaks(t_leak *cub)
{
    t_leak *current = cub;

    while (current != NULL)
    {
        printf("Leak at %p\n", current->address);
        current = current->next;
    }
}

int	parser(t_data *data)
{
	init(data);
	map_fill(data);
	if (ft_check(data))
		ft_errorv2(data, "Error\n");
	add_to_map(data);
	map_scan(data);
	printf("--------------------------------------------------------\n");
	// print_leaks(data->info->free);
	ft_free_all(data->info->free);
	exit(0);
	return (0);
}
