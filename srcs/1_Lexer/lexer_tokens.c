/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/17 14:53:53 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;
	char	quote;

	buf_pos = 0;
	while (data->line[data->pos] && !ft_isspace(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (is_quote(data->line[data->pos]))
		{
			quote = data->line[data->pos];
			buffer[buf_pos++] = data->line[data->pos++];
			while (data->line[data->pos] && data->line[data->pos] != quote)
				buffer[buf_pos++] = data->line[data->pos++];
			if (data->line[data->pos] == quote)
				buffer[buf_pos++] = data->line[data->pos++];
			else
				return (ft_putstr_fd("Minishell: unclosed quote\n", 2), NULL);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

static char	*get_token_value(t_token_type type)
{
	if (type == PIPE)
		return (ft_strdup("|"));
	if (type == REDIR_IN)
		return (ft_strdup("<"));
	if (type == REDIR_OUT)
		return (ft_strdup(">"));
	if (type == APPEND)
		return (ft_strdup(">>"));
	if (type == HEREDOC)
		return (ft_strdup("<<"));
	if (type == SEMICOLON)
		return (ft_strdup(";"));
	if (type == AND)
		return (ft_strdup("&"));
	if (type == AND_IF)
		return (ft_strdup("&&"));
	if (type == OR_IF)
		return (ft_strdup("||"));
	if (type == NOT)
		return (ft_strdup("!"));
	return (NULL);
}

static int	lexer_loop(t_data *data, t_token **tokens)
{
	char			*word;
	t_token_type	type;

	while (data->line[data->pos])
	{
		while (ft_isspace(data->line[data->pos]))
			data->pos++;
		if (!data->line[data->pos])
			break ;
		type = get_operator_type(data);
		if (type != WORD)
			word = get_token_value(type);
		else
			word = read_word(data);
		if (!word)
			return (free_tokens(tokens), 0);
		add_token(tokens, new_token(type, word));
		free(word);
		if (type != WORD)
			data->pos++;
	}
	return (1);
}

t_token	*lexer(char *line, t_env_var *env_vars)
{
	t_data			data;
	t_token			*tokens;

	data.line = line;
	data.env_vars = env_vars;
	tokens = NULL;
	data.pos = 0;
	if (!lexer_loop(&data, &tokens))
		return (NULL);
	return (tokens);
}
