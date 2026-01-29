/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:01:51 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/17 15:43:34 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
	{
		ft_error("Error\n:: ./cub3D_bonus Assets/maps/file.cub");
		return (1);
	}
	init_engin(&cub, av[1]);
	return (0);
}
