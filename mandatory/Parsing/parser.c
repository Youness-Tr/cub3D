/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/11 17:21:04 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

int ft_check(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (find_direction(data, data->map[i][j]))
            {
                // data->info->plyr.angle = PI / 2; chamal 3PI/2 janoub 0 sa3odia PI marikan;
                data->player_x = i;
                data->player_Y = j;
            }
            if (!is_valid_char(data->map[i][j]))
                return (1);
        }
        i++;
    }
    data->lines = i - 1;
    return 0;
}

void add_to_map(t_data *data)
{
    int i;
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
                data->map[i] = join_space(data->map[i], " ");
            data->map[i] = ft_strjoin(data->map[i], "\n");
        }
        i++;
    }
    data->map_len = data->map_w;
}

void map_fill(t_data *data)
{
    int i;
    int j;
    char *line;
    int fd;

    i = 0;
    j = 0;
    fd = open(data->file_path, O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        if (!data->stop)
        {
            ft_init(line, data);
            i++;
        }
        if (data->stop)
        {
            data->map[j] = ft_strdup(line);
            j++;
        }
        free(line);
        line = get_next_line(fd);
    }
    data->map[j] = NULL;
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
            if (data->map[i][j] == '0' || data->map[i][j] == 'N')
	        {
		        if (i == 0 || i == data->lines|| j == 0
			        || j == data->map_w - 2)
                {
                        printf ("i ::%i && j ::%i", data->lines, data->map_w);
			            ft_errorv2(data, "error::::: invalid map");
                }
		        if (data->map[i - 1][j] == ' ' || data->map[(i) + 1][j] == ' '
			        || data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
			            ft_errorv2(data, "error::::: invalid map");
	        }
        }
	}
}

int parser(t_data *data)
{
    init(data);
    map_fill(data);
    if (ft_check(data))
        ft_errorv2(data, "Error\n");
    add_to_map(data);
    map_scan(data);
    return (0);
}
