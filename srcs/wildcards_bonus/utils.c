/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:56:46 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/07 01:55:18 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_arg(t_list **args, char *content)
{
	t_list	*new;
	char	*data;

	data = ft_strdup(content);
	if (!data)
		return (0);
	new = ft_lstnew(data);
	if (!new)
		return (perror("malloc"), 0);
	ft_lstadd_back(args, new);
	return (1);
}
