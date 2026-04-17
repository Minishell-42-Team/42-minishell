/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 06:22:02 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/17 15:24:51 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	affect_command_param(t_command_ast *command, t_token *token)
{
	t_list	*node;

	node = NULL;
	if (!command->command)
	{
		command->command = ft_strdup(token->value);
		if (!command->command)
			return (0);
	}
	else
	{
		node = ft_lstnew(ft_strdup(token->value));
		if (!node)
			return (0);
		ft_lstadd_back(&command->args, node);
	}
	return (1);
}
