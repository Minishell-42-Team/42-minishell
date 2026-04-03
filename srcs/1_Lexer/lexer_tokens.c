/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/03 11:39:25 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_word_between_quotes(t_data *data, char quote)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;

	buf_pos = 0;
	data->pos++;
	while (data->line[data->pos] && data->line[data->pos] != quote
		&& buf_pos < 1023)
	{
		if (quote == '"' && data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos, data->env_vars);
			if (!tmp)
				return (NULL);
			buf_pos += ft_strlcpy(buffer + buf_pos, tmp, 1024 - buf_pos);
			free(tmp);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	if (data->line[data->pos] != quote)
		return (printf("error: unclosed quote. \n"), NULL);
	(buffer[buf_pos] = '\0', data->pos++);
	return (ft_strdup(buffer));
}

static char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;
	char	*tmp;

	buf_pos = 0;
	while (data->line[data->pos] && !ft_isspace(data->line[data->pos])
		&& !is_quote(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos, data->env_vars);
			if (!tmp)
				return (NULL);
			buf_pos += ft_strlcpy(buffer + buf_pos, tmp, 1024 - buf_pos);
			free(tmp);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

static char	*read_word(t_data *data)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;

	buf_pos = 0;
	while (data->line[data->pos] && !ft_isspace(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (is_quote(data->line[data->pos]))
			tmp = read_word_between_quotes(data, data->line[data->pos]);
		else
			tmp = read_normal_word(data);
		if (!tmp)
			return (NULL);
		buf_pos += ft_strlcpy(buffer + buf_pos, tmp, 1024 - buf_pos);
		free(tmp);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
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
		{
			add_token(tokens, new_token(type, NULL));
			data->pos++;
		}
		else
		{
			word = read_word(data);
			if (!word)
				return (free_tokens(tokens), 0);
			(add_token(tokens, new_token(WORD, word)), free(word));
		}
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
