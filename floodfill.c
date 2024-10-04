# include "Header/cub3d.h"

void count_spaces(t_data *data)
{
	int i = 0;
	int j = 0;
	data->space = 0;

	while (data->map_cp[i])
	{
		j = 0;
		while (data->map_cp[i][j])
		{
			if (data->map_cp[i][j] == ' ')
        		data->space++;
			j++;
		}
		i++;
	}
}

void	f_floodfill(char **map, int x, int z, t_data *data)
{
	if (x < 0 || x >= data->lines || z < 0 || z >= (ft_strlen(map[x]))
		|| map[x][z] == '1' || map[x][z] == 'H')
	{
		return ;
	}
	map[x][z] = 'H';
	f_floodfill(map, x -1, z, data);
	f_floodfill(map, x +1, z, data);
	f_floodfill(map, x, z -1, data);
	f_floodfill(map, x, z +1, data);
}

void	floodfill_check(t_data *data)
{
	int i = 0;
    int c = 0;
    int count = 0;
	f_floodfill(data->map_cp, data->player_x, data->player_Y, data);
	while (data->map_cp[i])
	{
		c = 0;
		while (data->map_cp[i][c])
		{
            // printf("%c", data->map_cp[i][c]);
			// if (data->map_cp[i][c] == '0') //i add this to solve problem of cadr of the map;
			// 	f_floodfill(data->map_cp, i, c, data);
			if (data->map_cp[i][c] == ' ')
                count++;
			c++;
		}
		i++;
	}
    if (count != data->space)
		printf("invalid map\n");
	printf("counter::%i && spaces::%i\n", count, data->space);
}


// char	*ft_strjoinedit(char *s1, char *s2)
// {
// 	char	*strs;
// 	int		t_len;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	t_len = (ft_strlen(s1) - 2) + ft_strlen(s2);
// 	strs = malloc((t_len + 1) * sizeof(char));
// 	if (!strs)
// 		return (NULL);
// 	ft_memmove(strs, s1, ft_strlen(s1));
// 	ft_memmove(strs + ft_strlen(s1), s2, ft_strlen(s2));
// 	strs[t_len] = '\0';
// 	return (strs);
// }