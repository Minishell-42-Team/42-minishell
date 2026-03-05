/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 01:53:40 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/18 16:09:17 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*element;

	element = *lst;
	if (new == NULL)
		return ;
	if (element == NULL)
	{
		*lst = new;
		return ;
	}
	while (element->next != NULL)
		element = element->next;
	element->next = new;
}
