/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:15:47 by ajabri            #+#    #+#             */
/*   Updated: 2024/09/15 10:03:53 by ajabri           ###   ########.fr       */
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_while(str, s, start, len);
	return (str);
}
