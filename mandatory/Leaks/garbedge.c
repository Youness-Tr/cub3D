/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youness <youness@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:50:38 by kali              #+#    #+#             */
/*   Updated: 2024/11/16 22:55:35 by youness          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/cub3d.h"

t_leak	*ft_lstlastv2(t_leak *lst)
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

void	ft_leaks_lstadd_back(t_leak **lst, t_leak *newx)
{
	t_leak	*node;

	if (!lst || !newx)
		return ;
	if (*lst)
	{
		node = ft_lstlastv2(*lst);
		node->next = newx;
	}
	else
	{
		*lst = newx;
	}
	    printf("Added new leak at %p to leaks list\n", newx->address);
}

void *ft_malloc(t_cub *cub, size_t size)
{
    void *res;
    t_leak *new_leak;

    res = malloc(size);
    if (!res)
        return (NULL);

    new_leak = (t_leak *)malloc(sizeof(t_leak));
    if (!new_leak)
    {
        free(res);
        return (NULL);
    }

    new_leak->address = res;
    new_leak->next = NULL;

    ft_leaks_lstadd_back(&cub->free, new_leak);

    // Debugging print
    printf("Allocated %zu bytes at %p, added to leaks list\n", size, res);

    return (res);
}
