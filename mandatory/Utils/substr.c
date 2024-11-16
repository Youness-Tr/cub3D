/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:15:47 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/16 23:22:53 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

static char	*ft_while(char *ptr, char *st, unsigned int star, size_t lent)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (st[i] && j < lent)
	{
		if (i >= star)
		{
			ptr[j] = st[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_substrv2(char *s, unsigned int start, size_t len, t_cub *cub)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (ft_strdupv2("", cub));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = (char *)ft_malloc(cub, (len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_while(str, s, start, len);
	return (str);
}
