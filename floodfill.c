# include "Header/cub3d.h"

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
			if (data->map_cp[i][c] == '0')
				f_floodfill(data->map_cp, i, c, data);
			if (data->map_cp[i][c] == ' ')
                count++;
			c++;
		}
		i++;
	}
    if (count != data->lines)
		printf("invalid map\n");
	printf("counter::%i && spaces::%i\n", count, data->space);
}