/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 10:51:57 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/17 15:36:05 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*tokens = NULL;
}

static t_token_type	get_operator_type_redir(char c, char next, t_data *data)
{
	if (c == '<' && next && next == '<')
	{
		data->pos++;
		return (HEREDOC);
	}
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
	{
		if (next && next == '>')
		{
			data->pos++;
			return (APPEND);
		}
		return (REDIR_OUT);
	}
	return (WORD);
}

t_token_type	get_operator_type(t_data *data)
{
	char	c;
	char	next;

	c = data->line[data->pos];
	next = data->line[data->pos + 1];
	if (c == '&' && next && next == '&')
	{
		data->pos++;
		return (AND_IF);
	}
	if (c == '&')
		return (AND);
	if (c == '|' && next && next == '|')
	{
		data->pos++;
		return (OR_IF);
	}
	if (c == '|')
		return (PIPE);
	if (c == '!')
		return (NOT);
	if (c == ';')
		return (SEMICOLON);
	return (get_operator_type_redir(c, next, data));
}

char	*token_type_str(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == REDIR_IN)
		return ("REDIR_IN");
	if (type == REDIR_OUT)
		return ("REDIR_OUT");
	if (type == APPEND)
		return ("APPEND");
	if (type == HEREDOC)
		return ("HEREDOC");
	return ("TOKEN_NONE");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("TYPE: %s", token_type_str(tokens->type));
		if (tokens->value)
			printf(" | VALUE: %s", tokens->value);
		printf("\n");
		tokens = tokens->next;
	}
}
