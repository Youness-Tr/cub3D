# include "../Header/cub3d.h"

// char	*ft_substr(char *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	s_len;
// 	char	*p;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start > s_len)
// 		return (ft_strdup(""));
// 	else if (s_len - start < len)
// 		return (ft_strdup(&s[start]));
// 	p = malloc((len + 1) * sizeof(char));
// 	if (!p)
// 		return (NULL);
// 	while (i < len && s[i])
// 	{
// 		p[i] = s[start];
// 		i++;
// 		start++;
// 	}
// 	p[i] = '\0';
// 	return (p);
// }

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



int is_valid_char(char c)
{
    if (c == '1' || c == '0' || c == ' ' || c == 'N' || c == '\n')
        return 1;
    return (0);
}

void init(t_data *data)
{
    data->stop = 0;
    data->space = 0;
    int len = 0;

    data->len = 0;
    len = count_len(data);
    data->map = malloc(sizeof(char *) * len);
    data->map_cp = malloc(sizeof(char *) * len);
}

