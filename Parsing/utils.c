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
		|| c == 'N' || c == 'W' 
		|| c == 'S' || c == 'E'|| c == '\n')
        return 1;
    return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void init(t_data *data)
{
    data->stop = 0;
    int len = 0;

	// data->info->parse.F = data->F;
	// data->F = NULL;
	data->len = 0;
	len = count_len(data);
    data->map = malloc(sizeof(char *) * len);
}

