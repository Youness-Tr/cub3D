/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:42:40 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/12/03 22:45:26 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

int	n_len(int n)
{
	long	result;
	int		i;

	i = 0;
	result = n;
	while (result != 0)
	{
		result = result / 10;
		i++;
	}
	return (i);
}

int	count_len(t_data *data)
{
	int		i;
	char	*line;
	char	*ext;
	int		fd;

	i = 0;
	ext = ft_substrv2(data->file_path, ft_strlen(data->file_path) - 4, 4,
			data->info);
	fd = open(data->file_path, O_RDONLY);
	if (fd == -1 || ft_strcmp(ext, ".cub"))
		ft_errorv2(data, "Error\n:: INVALID FILE");
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	return (i);
}

void	init(t_data *data)
{
	int	len;

	len = 0;
	data->stop = 0;
	data->len = 0;
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->c = 0;
	data->f = 0;
	len = count_len(data);
	if (len == 0)
		ft_errorv2(data, "Error\n:: EMPTY FILE");
	data->map = ft_malloc(data->info, sizeof(char *) * len);
}

void	door_checking(t_data *data, int i, int j)
{
	if (i == 0 || i == data->lines || j == 0 || j == data->map_w - 2)
		ft_errorv2(data, "Error\n:: INVALID MAP");
	if ((data->map[i - 1][j] != '1' && (data->map[i][j - 1] != '1'))
		|| (data->map[i - 1][j] != '1' && data->map[i][j + 1] != '1'))
		ft_errorv2(data, "Error\n:: INVALID MAP");
	if ((data->map[i + 1][j] != '1' && data->map[i][j + 1] != '1')
		|| (data->map[i + 1][j] != '1' && data->map[i][j - 1] != '1'))
		ft_errorv2(data, "Error\n:: INVALID MAP");
}

void	ft_errorv2(t_data *data, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
	ft_free_all(data->info->free);
	exit(1);
}
