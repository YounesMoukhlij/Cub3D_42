/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youmoukh <youmoukh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:27:07 by youmoukh          #+#    #+#             */
/*   Updated: 2024/07/29 10:14:45 by youmoukh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	add_back_garbage(t_delete **head, t_delete *node)
{
	if (!head || !node)
		return ;
	if (*head == NULL)
		lstaddfront_garbage(head, node);
	last_cmd_garbage(*head)->next = node;
	node->next = NULL;
}

void	free_list(t_delete **head)
{
	t_delete	*current;
	t_delete	*next;

	current = *head;
	while (current != NULL)
	{
		free(current->ptr);
		current->ptr = 0x0;
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	*ft_malloc(size_t size, int mode)
{
	static t_delete	*collecte;
	void			*str;

	str = NULL;
	if (mode == 0x1)
	{
		str = malloc(size);
		if (str == NULL)
			return (NULL);
		else
			add_back_garbage(&collecte, lstnew_garbage(str));
	}
	else
		free_list(&collecte);
	return (str);
}