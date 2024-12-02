/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:36:17 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/12/02 14:42:01 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

void	*get_value(char *s, unsigned int start, t_cub *cub)
{
	size_t	s_len;
	char	*ss;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	while (s[start] && s[start] == ' ')
		start++;
	while (s_len > 0 && s[s_len - 1] == ' ')
		s_len--;
	ss = ft_substrv2(s, start, s_len - start - 1, cub);
	return (ss);
}

int	check_color(char **p, int i, int j)
{
	int	count;

	count = 0;
	while (p[i])
	{
		j = 0;
		count = 0;
		while (p[i][j])
		{
			if (!ft_isdigit(p[i][j]) && p[i][j] != '\n' && p[i][j] != ' ')
				return (1);
			if (ft_isdigit(p[i][j]))
				count++;
			j++;
		}
		if (count == 0)
			return (1);
		i++;
	}
	if (i != 3)
		return (1);
	if ((!p || !p[0] || !p[1] || !p[2]) || (ft_atoi(p[0]) == -1
			|| ft_atoi(p[1]) == -1 || ft_atoi(p[2]) == -1))
		return (1);
	return (0);
}

int	get_haxe(char *s, unsigned int start, t_cub *cub)
{
	size_t	s_len;
	char	*ss;
	int		hexa;
	char	**db;

	if (!s)
		return (0);
	s_len = ft_strlen(s);
	while (s[start] && s[start] == ' ')
		start++;
	while (s_len > 0 && s[s_len - 1] == ' ')
		s_len--;
	ss = ft_substrv2(s, start, s_len - start, cub);
	db = ft_splitv2(ss, ',', cub);
	if ((check_color(db, 0, 0)))
	{
		ft_errorv2(&cub->parse, "ERROR :: INVALID COLOR FORMAT");
		return (0);
	}
	hexa = create_trgb(0, ft_atoi(db[0]), ft_atoi(db[1]), ft_atoi(db[2]));
	return (hexa);
}

void	ft_init(char *line, t_data *data)
{
	if (!strncmp("NO ", line, 3) && data->no == NULL)
		data->no = get_value(line, 2, data->info);
	else if (!strncmp("SO ", line, 3) && data->so == NULL)
		data->so = get_value(line, 2, data->info);
	else if (!strncmp("WE ", line, 3) && data->we == NULL)
		data->we = get_value(line, 2, data->info);
	else if (!strncmp("EA ", line, 3) && data->ea == NULL)
		data->ea = get_value(line, 2, data->info);
	else if (!strncmp("F ", line, 2) && data->f == 0)
		data->f = get_haxe(line, 1, data->info);
	else if (!strncmp("C ", line, 2) && data->c == 0)
		data->c = get_haxe(line, 1, data->info);
	else if (space_skip(line))
		data->stop = 0;
	else if (data->no && data->so && data->we && data->ea && data->f && data->c)
		data->stop = 1;
	else
		ft_errorv2(data, "ERROR :: INVALID DATA");
}

char	*join_space(char *s1, char *s2, t_cub *cub)
{
	int		len1;
	int		i;
	char	*str;

	i = 0;
	while (s1[i])
	{
		if (s1[i] == '\n')
			break ;
		i++;
	}
	str = ft_malloc(cub, (i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	len1 = 0;
	while (len1 < i)
	{
		str[len1] = s1[len1];
		len1++;
	}
	str[len1] = s2[0];
	str[len1 + 1] = '\0';
	return (str);
}
