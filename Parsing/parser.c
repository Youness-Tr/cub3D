/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 14:57:48 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Header/cub3d.h"

void *get_value(char *s, unsigned int start)
{
    size_t s_len;
    char *ss;

    if (!s)
        return (NULL);
    s_len = ft_strlen(s);
    while (s[start] && s[start] == ' ')
        start++;
    while (s_len > 0 && s[s_len - 1] == ' ')
        s_len--;
    ss = ft_substr(s, start, s_len - start);
    return (ss);
}

int get_haxe(char *s, unsigned int start)
{
    size_t s_len;
    char *ss;

    if (!s)
        return (0);
    s_len = ft_strlen(s);
    while (s[start] && s[start] == ' ')
        start++;
    while (s_len > 0 && s[s_len - 1] == ' ')
        s_len--;
    ss = ft_substr(s, start, s_len - start);
    char **db = ft_split(ss, ',');
    if (!db || !db[0] || !db[1] || !db[2])
    {
        free(ss);
        return 0;
    }
    int hexa = create_trgb(0, ft_atoi(db[0]), ft_atoi(db[1]), ft_atoi(db[2]));
    printf("color :: %x\n", hexa);
    free(ss);
    free(db);
    return (hexa);
}


void ft_init(char *line, t_data *data)
{
    if (!strncmp("NO", line, 2))
        data->NO = get_value(line, 2);
    else if (!strncmp("SO", line, 2))
        data->SO = get_value(line, 2);
    else if (!strncmp("WE", line, 2))
        data->WE = get_value(line, 2);
    else if (!strncmp("EA", line, 2))
        data->EA = get_value(line, 2);
    else if (!strncmp("F", line, 1))
        data->F = get_haxe(line, 1);
    else if (!strncmp("C", line, 1))
        data->C = get_haxe(line, 1);
    else if (!strncmp(" ", line, 1) || !strncmp("\n", line, 1))
        data->stop = 0;
    else
    {
        data->stop = 1;
    }
    printf("------------------------------------< %d\n", data->F);
}

int ft_check(t_data *data)
{
    int i = 0;
    int j;

    while (data->map[i])
    {
        j = -1;
        while (data->map[i][++j])
        {
            if (data->map[i][j] == 'N')
            {
                // data->info->plyr.angle = PI / 2; chamal 3PI/2 janoub 0 sa3odia PI marikan
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
    data->map_w = 0;

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
            j++;
        }
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
			            ft_error("error::::: invalid map");
                }
		        if (data->map[i - 1][j] == ' ' || data->map[(i) + 1][j] == ' '
			        || data->map[i][j - 1] == ' ' || data->map[i][j + 1] == ' ')
			            ft_error("error::::: invalid map");
	        }
        }
	}
}

int parser(t_data *data)
{
    init(data);
    map_fill(data);
    if (ft_check(data))
        ft_error("Error\n");
    add_to_map(data);
    map_scan(data);
    printf("NO ::%s", data->NO);
    printf("WE ::%s", data->WE);
    printf("SO ::%s", data->SO);
    printf("EA ::%s", data->EA);
    printf("-------------------------------------------\n");
    int i = 0;
    while (data->map[i])
    {
        printf("%s", data->map[i]);
        i++;
    }
    // exit(1);
    return (0);
}
