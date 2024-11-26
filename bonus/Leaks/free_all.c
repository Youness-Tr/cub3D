/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytarhoua <ytarhoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:28 by kali              #+#    #+#             */
/*   Updated: 2024/11/22 18:40:43 by ytarhoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d_bonus.h"

void	ft_free_all(t_leak *cub)
{
	t_leak	*next;

	while (cub != NULL)
	{
		next = cub->next;
		free(cub->address);
		free(cub);
		cub = next;
	}
	cub = NULL;
}

t_leak	*ft_leaks_lstlast(t_leak *lst)
{
	t_leak	*tmp;

	if (!lst)
		return (0);
	tmp = lst;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp);
}
