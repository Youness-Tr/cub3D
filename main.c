/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/22 16:13:39 by ajabri           ###   ########.fr       */
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
    else    
        data->test = "NOTHING";
}


int ft_check(t_data *data)
{
    int i = 0;

    while (data->array[i])
    {   
        if (data->array[i][0] == '1' || data->array[i][0] == '0')
        {
            if (data->array[i][0] != '1')
            {
                printf("dkhlat\n");
                return (1);
            }
            else if (data->array[i][strlen(data->array[i]) - 2] != '1')
            {
                return (1);
            }
        }
        i++;
    }
    return (0);
}

int main()
{
    int i = 0;
    t_data *data;
    char *line;

    int fd = open("./file", O_RDWR);

    line = get_next_line(fd);
    while (line)
    {
        // printf("%s", line);
        data->array[i] = ft_strdup(line);
        ft_init(line, data);
        line = get_next_line(fd);
        i++;
    }
    data->array[i] = NULL;
    printf("here\n");
    i = 0;
    if (ft_check(data))
        printf("Error\n");
    // while (data->array[i])
    // {
    //     printf("array[i] :: %s", data->array[i]);
    //     i++;
    // }
}