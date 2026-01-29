/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:52:05 by youness           #+#    #+#             */
/*   Updated: 2024/11/26 17:52:07 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putstrv2(const char *s, char *str)
{
	int	i;

	i = 0;
	if (!s || !str)
		return ;
	while (s[i] != '\0')
	{
		if (s[i] == '#' && s[i + 1] == 'S')
			ft_putstr(str);
		i++;
	}
}
