/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbedge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabri <ajabri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:50:38 by kali              #+#    #+#             */
/*   Updated: 2024/08/14 11:31:57 by ajabri           ###   ########.fr       */
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
}

t_leak	*ft_leaks_lstnew(void *var)
{
	t_leak	*lst;

	lst = (t_leak *)malloc(sizeof(t_leak));
	if (!lst)
		return (NULL);
	lst->address = var;
	lst->next = NULL;
	return (lst);
}

void	*ft_malloc(t_cub *cub, size_t size)
{
	void	*res;

	res = malloc(size + 1);
	if (!res)
		return (NULL);
	ft_leaks_lstadd_back(&cub->free, ft_leaks_lstnew(res));
	return (res);
}
