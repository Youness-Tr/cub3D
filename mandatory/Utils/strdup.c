/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:26:34 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/22 18:26:50 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

char	*ft_strdupv2(char *s1, t_cub *leak)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	str = ft_malloc(leak, (len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoinv2(char *s1, char *s2, t_cub *cub)
{
	char	*strs;
	int		t_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	t_len = ft_strlen(s1) + ft_strlen(s2);
	strs = ft_malloc(cub, (t_len + 1) * sizeof(char));
	if (!strs)
		return (NULL);
	ft_memmove(strs, s1, ft_strlen(s1));
	ft_memmove(strs + ft_strlen(s1), s2, ft_strlen(s2));
	strs[t_len] = '\0';
	return (strs);
}
