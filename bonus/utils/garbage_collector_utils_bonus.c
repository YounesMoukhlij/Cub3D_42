/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:27:39 by youmoukh          #+#    #+#             */
/*   Updated: 2024/08/17 14:16:02 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

t_delete	*lstnew_garbage(void *str)
{
	t_delete	*lst;

	lst = malloc(sizeof(t_delete));
	if (!lst)
		return (NULL);
	lst->ptr = str;
	lst->next = NULL;
	return (lst);
}

t_delete	*last_cmd_garbage(t_delete *lst)
{
	t_delete	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	lstaddfront_garbage(t_delete **head, t_delete *node)
{
	node->next = (*head);
	(*head) = node;
}
