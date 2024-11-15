/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:29:02 by ajabri            #+#    #+#             */
/*   Updated: 2024/10/12 12:35:01 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/get_next_line.h"


int	ft_strlen(char *c)
{
	int	i;

	i = 0;
	if (!c)
		return (0);
	while (c[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char)c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (NULL);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	str = malloc((len + 1) * sizeof(char));
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

void	*ft_memmove(void *dst, void *src, size_t n)
{
	size_t	i;
	char	*s;
	char	*dest;

	i = 0;
	dest = (char *)dst;
	s = (char *)src;
	if ((s == NULL && dst == NULL) || n == 0)
		return (dst);
	if (dest > s)
	{
		while (n--)
		{
			dest[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			dest[i] = s[i];
			i++;
		}
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
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
	strs = malloc((t_len + 1) * sizeof(char));
	if (!strs)
		return (NULL);
	ft_memmove(strs, s1, ft_strlen(s1));
	ft_memmove(strs + ft_strlen(s1), s2, ft_strlen(s2));
	strs[t_len] = '\0';
	free(s1); // added by VENOM
	return (strs);
}

////////////////////////////////////

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
