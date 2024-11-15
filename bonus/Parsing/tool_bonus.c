/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:36:17 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/15 12:11:24 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	*get_value(char *s, unsigned int start)
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
	ss = ft_substr(s, start, s_len - start - 1);
	return (ss);
}

int	get_haxe(char *s, unsigned int start)
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
	ss = ft_substr(s, start, s_len - start);
	db = ft_split(ss, ',');
	if (!db || !db[0] || !db[1] || !db[2])
	{
		free(ss);
		ft_free(db);
		ft_error("color error");//!free textures
		return (0);
	}
	hexa = create_trgb(0, ft_atoi(db[0]), ft_atoi(db[1]), ft_atoi(db[2]));
	free(ss);
	ft_free(db);
	return (hexa);
}

void	ft_init(char *line, t_data *data)
{
	if (!strncmp("NO ", line, 3))
		//? space to avoid this case NOOO ./texture.xpm
		data->no = get_value(line, 2);
	else if (!strncmp("SO ", line, 3))
		data->so = get_value(line, 2);
	else if (!strncmp("WE ", line, 3))
		data->we = get_value(line, 2);
	else if (!strncmp("EA ", line, 3))
		data->ea = get_value(line, 2);
	else if (!strncmp("F ", line, 2))
		data->f= get_haxe(line, 1);
	else if (!strncmp("C ", line, 2))
		data->c= get_haxe(line, 1);
	else if (!strncmp(" ", line, 1) || !strncmp("\n", line, 1))
		data->stop = 0;
	else if (data->no && data->so && data->we && data->ea && data->f&& data->c)
		data->stop = 1;
	else
		ft_error("args error"); //! i have to free here
}

char	*join_space(char *s1, char *s2)
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
	str = malloc((i + 2) * sizeof(char));
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
	free(s1);
	return (str);
}
