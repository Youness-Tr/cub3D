/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:28 by kali              #+#    #+#             */
/*   Updated: 2024/11/16 22:45:53 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

void	ft_free_all(t_leak *cub)
{
	// t_leak	*current;
	t_leak	*next;

	// current = cub;
		// printf("address == %p\n", current->address);
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
