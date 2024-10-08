/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/08 11:19:39 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

void ft_init(char *line, t_data *data)
{
    if (!strncmp("NO", line, 2))
        data->NO = ft_substr(line, 2, strlen(&line[2]));
    else if (!strncmp("SO", line, 2))
        data->SO = ft_substr(line, 2, strlen(&line[2]));
    else if (!strncmp("WE", line, 2))
        data->WE = ft_substr(line, 2, strlen(&line[2]));
    else if (!strncmp("EA", line, 2))
        data->EA = ft_substr(line, 2, strlen(&line[2]));
    else if (!strncmp("F", line, 1))
        data->F = ft_substr(line, 1, strlen(&line[1]));
    else if (!strncmp("C", line, 1))
        data->F = ft_substr(line, 1, strlen(&line[1]));
    else if (!strncmp(" ", line, 1) || !strncmp("\n", line, 1))
        data->stop = 0;
    else
    {
        data->stop = 1;
    }
}

int ft_check(t_data *data)
{
    int i = 0;

    while (data->map[i])
    {
        if (data->map[i][0] != '1' && data->map[i][0] != ' ')
            ft_error("Error : map not valid"); // return (1);

        if (data->map[i][strlen(data->map[i]) - 2] != '1')
            return (1);

        for (int j = 0; data->map[i][j]; j++)
        {
            if (data->map[i][j] == 'N')
            {
                data->player_x = i;
                data->player_Y = j;
            }
            if (i == 0 && !is_valid_char(data->map[i][j]))
                return (1);

            if (!is_valid_char(data->map[i][j]))
                return (1);
        }
        i++;
    }

    data->lines = i - 1;
    for (int j = 0; data->map[data->lines][j]; j++)
    {
        if (!is_valid_char(data->map[data->lines][j]))
            return printf("Invalid character in last row\n"), 1;
    }
    return 0;
}

char	*join_space(char *s1, char *s2)
{
	int		len1;
    int     i;
	char	*str;

    i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
    {
        if (s1[i] == '\n')
            break;
        i++;
    }
	str = malloc((i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	len1 = 0;
	while (len1 < i)
	{
		str[len1] = s1[len1];
		len1++;
	}
	str[len1] = s2[0];
	str[len1 + 1] = '\0';
	return (str);
}


void add_to_map(t_data *data)
{
    int i = 0;
    int big = 0;

    while (data->map_cp[i])
    {
        if (ft_strlen(data->map_cp[i]) > big)
            big = ft_strlen(data->map_cp[i]);
        i++;
    }
    i = 0;
    while (data->map_cp[i])
    {
        if (ft_strlen(data->map_cp[i]) < big)
        {
            while (ft_strlen(data->map_cp[i]) < big)
            {
                data->map_cp[i] = join_space(data->map_cp[i], " ");
                data->map[i] = join_space(data->map[i], " ");
            }
            data->map_cp[i] = ft_strjoin(data->map_cp[i], "\n");
            data->map[i] = ft_strjoin(data->map[i], "\n");
        }
        i++;
    }
    data->map_len = big;
}

int count_len(t_data *data)
{
    int i = 0;
    char *line;

    int fd = open(data->file_path, O_RDONLY);
    if (fd == -1)
        ft_error("invalid path\n");
    line = get_next_line(fd);
    while (line)
    {
        i++;
        line = get_next_line(fd);
    }
    return i;
}

void map_fill(t_data *data)
{
    int i = 0;
    int j = 0;
    char *line;
    int fd = open(data->file_path, O_RDONLY);
    if (fd == -1)
        ft_error("invalid path\n");
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
            data->map_cp[j] = ft_strdup(line);
            j++;
        }
        line = get_next_line(fd);
    }
    data->map[j] = NULL;
    data->map_cp[j] = NULL;
}

int parser(t_data *data)
{
    init(data);
    map_fill(data);
    if (ft_check(data))
        ft_error("Error\n");
    add_to_map(data);
    int i = 0;
    count_spaces(data);
    floodfill_check(data);
    //here check for spaces;
    // printf("NO :: %s", data->NO);
    // printf("WE :: %s", data->WE);
    // printf("SO :: %s", data->SO);
    // printf("EA :: %s", data->EA);
    // printf("-------------------------------------------\n");
    while (data->map_cp[i])
    {
        printf("%s", data->map_cp[i]);
        i++;
    }
    exit(1);
    return (0);
}
