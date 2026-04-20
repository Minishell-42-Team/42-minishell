/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/19 14:00:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_add_redir_to_list(t_redir_file **head, t_redir_file *node)
{
	t_redir_file	*tmp;

	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

static int	ft_fill_redir(t_redir_file *node, t_token_type type, char *file)
{
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
		return (0);
	return (1);
}

int	ft_addredir(t_redir_file **head, t_token_type type, char *file)
{
	t_redir_file	*node;

	if (!file)
		return (0);
	node = (t_redir_file *)malloc(sizeof(t_redir_file));
	if (!node)
		return (0);
	if (!ft_fill_redir(node, type, file))
	{
		free(node);
		return (0);
	}
	ft_add_redir_to_list(head, node);
	return (1);
}
