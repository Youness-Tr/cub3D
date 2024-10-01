/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/01 14:01:28 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*p;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	else if (s_len - start < len)
		return (ft_strdup(&s[start]));
	p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (i < len && s[i])
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

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
        // data->array[*i] = NULL;
        data->stop = 1;
        // *i = -1;
    }
}
int ft_check(t_data *data)
{
    int i = 0;
    int j = 0;

    while (data->map[i])
    {
        j = 0;
        if (data->map[i][0] != '1' && data->map[i][0] != ' ')
        {
            printf("dkhlat\n");
            return (1);
        }
        // printf("heeeeere\n");
        if (data->map[i][strlen(data->map[i]) - 2] != '1')
        {
            printf("ayih\n");
            return (1);
        }
        while (data->map[i][j])
        {
            if (i == 0)
            {
                if (data->map[i][j] != '1' && data->map[i][j] != ' '
                    && data->map[i][j] != '\n')
                    return (1);
            }
            if (data->map[i][j] != '1' && data->map[i][j] != '0'
                && data->map[i][j] != ' ' && data->map[i][j] != 'N'
                && data->map[i][j] != '\n')
            {
                printf("hna\n");
                return (1);
            }
            // printf("%c\n", data->map[i][j]);
            j++;
        }
        i++;
    }
    j = 0;
    i = i - 1;
    while(data->map[i][j])
    {
        if (data->map[i][j] != '1' && data->map[i][j] != ' '
            && data->map[i][j] != '\n')
            return (1);
        j++;
    }
    return (0);
}

int main()
{
    int i = 0;
    int j = 0;
    t_data data;
    char *line;
    data.stop = 0;

    int fd = open("./file", O_RDONLY);
    if (fd == -1)
    {
        printf("Error\n");
        return (1);
    }
    data.map = malloc(sizeof(char *) * 30);//i have to count how much space that i need to allocate;
    line = get_next_line(fd);
    while (line)
    {
        if (!data.stop)
        {
            // data.array[i] = strcpy(data.array[i], line);
            ft_init(line, &data);
            i++;
        }
        if (data.stop)
        {
            data.map[j] = ft_strdup(line);
            j++;
        }
        line = get_next_line(fd);
    }
    // data.array[i] = NULL;
    data.map[j] = NULL;
    // printf("here\n");
    if (ft_check(&data))
        printf("Error\n");
    //here check for spaces;
    // printf("NO :: %s", data.NO);
    // printf("WE :: %s", data.WE);
    // printf("SO :: %s", data.SO);
    // printf("EA :: %s", data.EA);
    // printf("-------------------------------------------\n");
    i = 0;
    while (data.map[i])
    {
        printf("%s", data.map[i]);
        i++;
    }
}