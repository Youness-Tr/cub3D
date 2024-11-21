/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:31:53 by ytarhoua          #+#    #+#             */
/*   Updated: 2024/11/19 15:33:16 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mandatory/Header/cub3d.h"

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 500, 500, "test");
    mlx_loop(mlx);
    return 0;
}