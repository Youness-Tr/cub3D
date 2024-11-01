/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:56:34 by ajabri            #+#    #+#             */
/*   Updated: 2024/11/01 16:58:02 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "Header/cub3d.h"


int main(int ac, char **av)
{
    t_cub cub;

    if (ac != 2)
        ft_error("Error: ./cub3D Assets/maps/file.cub");
    init_engin(&cub, av[1]);
    return (0);
}
