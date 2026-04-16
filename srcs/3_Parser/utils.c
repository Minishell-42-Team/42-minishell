/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 06:22:02 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/13 15:44:21 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_type_redir(t_token *token)
{
	return (token->type == APPEND || token->type == HEREDOC
		|| token->type == REDIR_IN || token->type == REDIR_OUT);
}

void	affect_token(t_token **token, t_token *token_to_be)
{
	*token = token_to_be;
}

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

static void	ft_clear_redir(t_redir_file **head)
{
	t_redir_file	*current_redir;
	t_redir_file	*redir_to_free;

	if (!head || !*head)
		return ;
	current_redir = *head;
	while (current_redir)
	{
		redir_to_free = current_redir;
		current_redir = current_redir->next;
		if (redir_to_free->type == HEREDOC && redir_to_free->heredoc_fd > 0)
			close(redir_to_free->heredoc_fd);
		free(redir_to_free->file);
		free(redir_to_free);
	}
	*head = NULL;
}

void	ft_free_command(t_command_ast **command)
{
	t_command_ast	*current_command;
	t_command_ast	*command_to_free;

	if (!command || !*command)
		return ;
	current_command = *command;
	while (current_command)
	{
		command_to_free = current_command;
		current_command = current_command->next;
		if (command_to_free->command)
			free(command_to_free->command);
		if (command_to_free->args)
			ft_lstclear(&command_to_free->args, free);
		ft_clear_redir(&command_to_free->redirs);
		free(command_to_free);
	}
	*command = NULL;
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i = 0;
	int		j = 0;
	char	quote = 0;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && quote == 0)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
