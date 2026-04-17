/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 06:22:02 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/17 15:25:21 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	is_quote_start(char c, char quote)
{
	if ((c == '\'' || c == '"') && quote == 0)
		return (1);
	return (0);
}

static void	handle_quote_state(char c, int *i, char *quote)
{
	if (is_quote_start(c, *quote))
	{
		*quote = c;
		(*i)++;
	}
	else if (c == *quote)
	{
		*quote = 0;
		(*i)++;
	}
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote_start(str[i], quote) || str[i] == quote)
			handle_quote_state(str[i], &i, &quote);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
