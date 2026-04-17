/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 04:51:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/17 15:09:06 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_file	*create_redir_node(t_token_type type, char *file)
{
	t_redir_file	*node;

	node = (t_redir_file *)malloc(sizeof(t_redir_file));
	if (!node)
		return (0);
	node->next = NULL;
	node->type = type;
	node->heredoc_fd = -1;
	if (type == HEREDOC)
	{
		node->quoted = has_quotes(file);
		node->file = remove_quotes(file);
	}
	else
	{
		node->quoted = 0;
		node->file = ft_strdup(file);
	}
	if (!node->file)
		return (free(node), NULL);
	return (node);
}

void	add_redir_back(t_redir_file **head, t_redir_file *node)
{
	t_redir_file	*tmp;

	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	is_type_redir(t_token *token)
{
	return (token->type == APPEND || token->type == HEREDOC
		|| token->type == REDIR_IN || token->type == REDIR_OUT);
}

void	affect_token(t_token **token, t_token *token_to_be)
{
	*token = token_to_be;
}
