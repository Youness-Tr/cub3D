/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 12:28:14 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/15 12:04:46 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

static size_t	ft_words(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static void	malloc_error_free(char **ret, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		free(ret[j]);
		j++;
	}
	free(ret);
}

static int	ft_mini_malloc(char **ptr, char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				s++;
			ptr[i] = ft_substr(s - len, 0, len);
			if (!ptr[i])
			{
				malloc_error_free(ptr, i);
				return (0);
			}
			i++;
		}
		else
			s++;
	}
	ptr[i] = NULL;
	return (1);
}

char	**ft_split(char *s, char c)
{
	char	**dp;

	if (!s)
		return (NULL);
	dp = malloc(sizeof(char *) * (ft_words(s, c) + 1));
	if (!dp)
		return (NULL);
	if (!ft_mini_malloc(dp, s, c))
		return (NULL);
	return (dp);
}
