/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 04:51:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/07 00:14:27 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command_ast	*init_command(void)
{
	t_command_ast	*command;

	command = (t_command_ast *)malloc(sizeof(t_command_ast));
	if (!command)
		return (NULL);
	command->next = NULL;
	command->command = NULL;
	command->args = NULL;
	command->redirs = NULL;
	return (command);
}

static int	ft_addredir(t_redir_file **head, t_token_type type, char *file)
{
	t_redir_file	*node;
	t_redir_file	*node_tmp;

	if (!file)
		return (0);
	node = (t_redir_file *)malloc(sizeof(t_redir_file));
	if (!node)
		return (0);
	node->next = NULL;
	node->type = type;
	node->file = ft_strdup(file);
	if (!node->file)
		return (free(node), 0);
	if (!*head)
		*head = node;
	else
	{
		node_tmp = *head;
		while (node_tmp->next)
			node_tmp = node_tmp->next;
		node_tmp->next = node;
	}
	return (1);
}

int	get_command_param(t_command_ast *command, t_token **curr_token)
{
	if (!(*curr_token))
		return (1);
	else if ((*curr_token)->type == PIPE && (*curr_token)->next)
		return (affect_token(curr_token, (*curr_token)->next), 1);
	else if ((*curr_token)->type == WORD && (*curr_token)->value)
	{
		if (!affect_command_param(command, *curr_token))
			return (0);
	}
	else if (is_type_redir(*curr_token) && (*curr_token)->next)
	{
		if ((*curr_token)->next->type != WORD || !ft_addredir(&command->redirs,
				(*curr_token)->type, (*curr_token)->next->value))
			return (0);
		*curr_token = (*curr_token)->next;
	}
	else
		return (0);
	*curr_token = (*curr_token)->next;
	if (get_command_param(command, curr_token))
		return (1);
	return (0);
}

static t_command_ast	*get_commands(t_token *tokens)
{
	t_token			*curr_token;
	t_command_ast	*cmds;
	t_command_ast	*current_cmd;

	if (!tokens)
		return (NULL);
	cmds = init_command();
	if (!cmds)
		return (NULL);
	current_cmd = cmds;
	curr_token = tokens;
	while (get_command_param(current_cmd, &curr_token) && curr_token)
	{
		current_cmd->next = init_command();
		if (!current_cmd->next)
			return (ft_free_command(&cmds), NULL);
		current_cmd = current_cmd->next;
	}
	if (!curr_token)
		return (cmds);
	return (ft_free_command(&cmds), NULL);
}

t_command_ast	*parser(t_token *tokens)
{
	t_command_ast	*cmds;
	t_command_ast	*node;

	if (!tokens)
		return (NULL);
	cmds = get_commands(tokens);
	if (!cmds)
		return (printf("error: parsing fail.\n"), NULL);
	node = cmds;
	while (node)
	{
		if (!get_matched_args(node))
			return (ft_free_command(&cmds), NULL);
		node = node->next;
	}
	return (cmds);
}
