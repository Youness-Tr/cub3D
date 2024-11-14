/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:42:40 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/14 12:43:01 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

static int	n_len(int n)
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

char	*ft_itoa(int n)
{
	int		i;
	long	result;
	char	*str;

	i = 0;
	if (n <= 0)
		i++;
	i += n_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	result = (long)n;
	str[i] = '\0';
	if (result < 0)
		result *= -1;
	while (i)
	{
		str[--i] = result % 10 + 48;
		result /= 10;
	}
	if (n < 0)
		str[i] = '-';
	return (str);
}

int	count_len(t_data *data)
{
	int		i;
	char	*line;
	char	*ext;
	int		fd;

	i = 0;
	ext = ft_substr(data->file_path, ft_strlen(data->file_path) - 4, 4);
	fd = open(data->file_path, O_RDONLY);
	if (fd == -1 || ft_strcmp(ext, ".cub"))
	{
		free(ext);
		ft_error("invalid path");
	}
	line = get_next_line(fd);
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(ext);
	return (i);
}

void	init(t_data *data)
{
	int	len;

	len = 0;
	data->stop = 0;
	data->len = 0;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->C = 0;
	data->F = 0;
	len = count_len(data);
	if (len == 0)
		ft_error("empty file");
	data->map = malloc(sizeof(char *) * len);
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
	ft_free(data->map);
	free(data->EA);
	free(data->NO);
	free(data->SO);
	free(data->WE);
	exit(1);
}
