/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:51 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/15 12:01:57 by ajabri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
	{
		ft_error("Error: ./cub3D Assets/maps/file.cub");
		return (1);
	}
	init_engin(&cub, av[1]);
	return (0);
}
