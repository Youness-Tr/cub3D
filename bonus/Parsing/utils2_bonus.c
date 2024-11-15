/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:42:40 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/15 12:12:36 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

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
	data->no = NULL;
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->c= 0;
	data->f= 0;
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
	free(data->ea);
	free(data->no);
	free(data->so);
	free(data->we);
	exit(1);
}
