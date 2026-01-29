/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:56:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/12/17 15:43:53 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Header/cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	if (ac != 2)
	{
		ft_error("Error\n:: ./cub3D Assets/maps/file.cub");
		return (1);
	}
	init_engin(&cub, av[1]);
	return (0);
}
