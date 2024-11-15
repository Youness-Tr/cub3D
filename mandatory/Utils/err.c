/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:14:56 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/15 11:59:52 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	ft_error(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(2, &s[i], 1);
		i++;
	}
	write(2, "\n", 1);
	exit(1);
}
