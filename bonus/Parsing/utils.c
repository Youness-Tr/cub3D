# include "../Header/cub3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	if (!big && len == 0)
		return (NULL);
	if (little[b] == '\0')
		return ((char *)big);
	while (big[b] != '\0' && b < len)
	{
		l = 0;
		while (big[b + l] == little[l] && big[b + l] != '\0' && (b + l < len))
		{
			l++;
		}
		if (little[l] == '\0')
			return ((char *)&big[b]);
		b++;
	}
	return (NULL);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			m;
	long long	result;

	m = 1;
	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		m *= -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result *= 10;
		result += nptr[i] - 48;
		i++;
	}
	return (result * m);
}

int is_valid_char(char c)
{
    if (c == '1' || c == '0' || c == ' '
	|| c == 'N' || c == 'S' || c == 'W'
	|| c == 'E'|| c == '\n')
        return 1;
    return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

// void file_check(char *file)
// {
// 	char *map;

// 	char *ext = ft_substr(file, ft_strlen(file) - 4, 4);
// 	int i = ft_strlen(file);
// 	while (i > 0)
// 	{
// 		if (file[i] == '/')
// 		{
// 			map = ft_substr(file, i, ft_strlen(file) - i);
// 			break;
// 		}
// 		i++;
// 	}
// 	if (ft_strcmp(ext, ".cub") || ft_strlen(map) <= 4)
// 	{
// 		free(ext);
// 		free(map);
// 		ft_error("invalid path");
// 	}
// }

int count_len(t_data *data)
{
    int i = 0;
    char *line;

	// file_check(data->file_path);
	char *ext = ft_substr(data->file_path, ft_strlen(data->file_path) - 4, 4);
    int fd = open(data->file_path, O_RDONLY);
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
	return i;
}

void init(t_data *data)
{
    int len = 0;
    data->stop = 0;
	data->len = 0;
	len = count_len(data);
	if (len == 0)
		ft_error("empty file");
    data->map = malloc(sizeof(char *) * len);
}

void ft_errorv2(t_data *data ,char *s)
{
    int i;
    i = 0;
    while (s[i])
    {
        write(2,&s[i], 1);
        i++;
    }
    write(2,"\n", 1);
    ft_free(data->map);
    free(data->EA);
    free(data->NO);
    free(data->SO);
    free(data->WE);
    exit(1);
}

void ft_exit(t_data *data)
{
	ft_free(data->map);
    free(data->EA);
    free(data->NO);
    free(data->SO);
    free(data->WE);
    exit(0);
}

void ft_free(char **p)
{
    int i = 0;
    while (p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
}