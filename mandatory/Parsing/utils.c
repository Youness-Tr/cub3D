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
		ft_error("not a number"); //?to make sure it's in right fomat 
		//! i have to free here
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
	if ((result * m) > 255)
		ft_error("not valid number"); //! i have to free here
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