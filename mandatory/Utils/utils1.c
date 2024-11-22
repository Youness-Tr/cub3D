/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:36:52 by lissam            #+#    #+#             */
/*   Updated: 2024/10/06 11:42:10 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

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

// int	ft_strcmp(char *ptr1, char *ptr2)
// {
// 	int	i;

// 	i = 0;
// 	while (ptr1[i] == ptr2[i] && ptr1[i] != '\0' && ptr2[i] != '\0')
// 		i++;
// 	return (ptr1[i] - ptr2[i]);
// }

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
