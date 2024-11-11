# include "../Header/cub3d.h"

static	int	n_len(int n)
{
	long	result;
	int		i;

	i = 0;
	result = n;
	while (result != 0)
	{
		result = result / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	result;
	char	*str;

	i = 0;
	if (n <= 0)
		i++;
	i += n_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	result = (long)n;
	str[i] = '\0';
	if (result < 0)
		result *= -1;
	while (i)
	{
		str[--i] = result % 10 + 48;
		result /= 10;
	}
	if (n < 0)
		str[i] = '-';
	return (str);
}

int count_len(t_data *data)
{
    int i;
    char *line;

	i = 0;
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
    int len;
 
	len = 0;
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
    int i;

	i = 0;
    while (p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
}
