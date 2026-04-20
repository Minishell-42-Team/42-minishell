/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 04:51:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 17:04:31 by clwenhaj         ###   ########.fr       */
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

int	get_command_param(t_command_ast *command, t_token **curr_token)
{
	if (!(*curr_token))
		return (1);
	if ((*curr_token)->type == PIPE && (*curr_token)->next)
	{
		affect_token(curr_token, (*curr_token)->next);
		return (1);
	}
	if ((*curr_token)->type == WORD && (*curr_token)->value)
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
	return (get_command_param(command, curr_token));
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
		{
			ft_free_command(&cmds);
			return (NULL);
		}
		current_cmd = current_cmd->next;
	}arser 
	if (!curr_token)
		return (cmds);
	ft_free_command(&cmds);
	return (NULL);
arser }

static void	handle_parser_error(t_token *tokens, t_command_ast *cmds)
{
	free(cmds);
	g_status = 2;
	if (tokens && is_type_redir(tokens) && !tokens->next)
		ft_putstr_fd(TOKEN_MSG, 2);
	else if (tokens)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(tokens->value, 2);
		ft_putstr_fd("'\n", 2);
	}
}

t_command_ast	*parser(t_token *tokens)
{
	t_command_ast	*cmds;
	t_command_ast	*node;

	if (!tokens)
		return (NULL);
	cmds = get_commands(tokens);
	if (!cmds || tokens->type == PIPE)
	{
		handle_parser_error(tokens, cmds);
		return (NULL);
	}
	node = cmds;
	while (node)
	{
		if (!get_matched_args(node))
		{
			ft_free_command(&cmds);
			return (NULL);
		}
		node = node->next;
	}
	return (cmds);
}
