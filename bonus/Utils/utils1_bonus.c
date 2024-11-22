/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:36:52 by lissam            #+#    #+#             */
/*   Updated: 2024/11/21 12:04:31 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

int	get_win_h(char **av)
{
	int	h;

	h = 0;
	if (!av)
		return (0);
	while (av[h])
		h++;
	return (h);
}

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
