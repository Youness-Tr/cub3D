/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:03:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/04 15:26:06 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Header/cub3d.h"

int	check_path(char *argv, t_data *data)
{
	char	*str;
	int		len;

	len = ft_strlen(argv);
    data->file_path = argv;
	if (len > 4 && (ft_strnstr(argv, "/.", len) == NULL))
	{
		str = ft_substr(argv, (len - 4), 4);
		if ((ft_strcmp(str, ".cub")) == 0)
		{
			free(str);
			return (0);
		}
		free(str);
	}
	return (1);
}

void ft_error(char *str)
{
    write(2, str, ft_strlen(str));
    exit (1);
}

int main(int ac, char **av)
{
    t_data data;
    int i = 0;

	if (ac != 2 || check_path(av[1], &data) == 1)
		ft_error("invalid path\n");
    parser(&data);
    // printf("NO :: %s", data.NO);
    // printf("WE :: %s", data.WE);
    // printf("SO :: %s", data.SO);
    // printf("EA :: %s", data.EA);
    // printf("-------------------------------------------\n");
    while (data.map_cp[i])
    {
        printf("%s", data.map_cp[i]);
        i++;
    }
}