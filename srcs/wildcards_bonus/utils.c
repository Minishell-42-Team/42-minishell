/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:56:46 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/03 10:15:52 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_arg(t_list **head, t_list **node_to_free)
{
	t_list	*node;
	t_list	*node_save;

	if (!*head)
		return ;
	if (*head == *node_to_free)
	{
		*head = (*head)->next;
		ft_lstdelone(*node_to_free, free);
		return ;
	}
	node = (*head)->next;
	node_save = *head;
	while (node)
	{
		if (node == *node_to_free)
		{
			node_save->next = node->next;
			ft_lstdelone(*node_to_free, free);
			return ;
		}
		node_save = node;
		node = node->next;
	}
}
