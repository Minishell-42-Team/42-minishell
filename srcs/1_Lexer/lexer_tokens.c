/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 15:54:24 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/23 18:48:20 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Lexer :
// Initialise index i
// Skip espaces
// Identifie type
// Appelle une fonction spécialisée
// Ajoute token à la liste
// Verifie les erreurs (ENCORE A VERIFIER TOTALEMENT!!!)
// Encore quelques fuites de memoire a gerer

#include "minishell.h"
//*************************************************************//

t_token_type	get_operator_type(t_data *data)
{
	char	c;

	c = data->line[data->pos];
	if (c == '|')
		return (PIPE);
	if (c == '>' && data->line[data->pos + 1]
		&& data->line[data->pos + 1] == '>')
	{
		data->pos++;
		return (APPEND);
	}
	if (c == '<' && data->line[data->pos + 1]
		&& data->line[data->pos + 1] == '<')
	{
		data->pos++;
		return (HEREDOC);
	}
	if (c == '<')
		return (REDIR_IN);
	if (c == '>')
		return (REDIR_OUT);
	return (WORD);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

char	*read_word_between_quotes(t_data *data, char quote)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;
	int		i;

	buf_pos = 0;
	data->pos++;
	while (data->line[data->pos]
		&& data->line[data->pos] != quote && buf_pos < 1023)
	{
		if (quote == '"' && data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos, data->env_vars);
			if (!tmp)
				return (NULL);
			i = 0;
			while (tmp[i] && buf_pos < 1023)
				buffer[buf_pos++] = tmp[i++];
			free(tmp);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	if (data->line[data->pos] == quote)
		data->pos++;
	else
	{
		printf("syntax error: unclosed quote %c\n", quote);
		return (NULL);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

char	*read_normal_word(t_data *data)
{
	char	buffer[1024];
	int		buf_pos;
	char	*tmp;
	int		i;

	buf_pos = 0;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !is_quote(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (data->line[data->pos] == '$')
		{
			data->pos++;
			tmp = expand_variable(data->line, &data->pos, data->env_vars);
			if (!tmp)
				return (NULL);
			i = 0;
			while (tmp[i] && buf_pos < 1023)
			{
				buffer[buf_pos] = tmp[i];
				buf_pos++;
				i++;
			}
			free(tmp);
		}
		else
			buffer[buf_pos++] = data->line[data->pos++];
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

char	*read_word(t_data *data)
{
	char	buffer[1024];
	char	*tmp;
	int		buf_pos;
	int		i;

	buf_pos = 0;
	while (data->line[data->pos]
		&& !ft_isspace(data->line[data->pos])
		&& !is_operator(data->line[data->pos]))
	{
		if (is_quote(data->line[data->pos]))
			tmp = read_word_between_quotes(data, data->line[data->pos]);
		else
			tmp = read_normal_word(data);
		if (!tmp)
			return (NULL);
		i = 0;
		while (tmp[i] && buf_pos < 1023)
		{
			buffer[buf_pos] = tmp[i];
			buf_pos++;
			i++;
		}
		free(tmp);
	}
	buffer[buf_pos] = '\0';
	return (ft_strdup(buffer));
}

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new)
{
	t_token	*node;

	node = NULL;
	if (!*head)
	{
		*head = new;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
	}
}

t_token	*lexer(char *line, t_env_var *env_vars)
{
	t_data			data;
	t_token			*tokens;
	char			*word;
	t_token			*tok;
	t_token_type	type;

	data.line = line;
	data.pos = 0;
	data.env_vars = env_vars;
	tokens = NULL;
	while (data.line[data.pos])
	{
		while (ft_isspace(data.line[data.pos]))
			data.pos++;
		if (!data.line[data.pos])
			break ;
		type = get_operator_type(&data);
		if (type != WORD)
		{
			add_token(&tokens, new_token(type, NULL));
			data.pos++;
		}
		else
		{
			word = read_word(&data);
			if (!word)
				return (free_tokens(tokens), NULL);
			tok = new_token(WORD, word);
			if (!tok)
				return (free(word), free_tokens(tokens), NULL);
			add_token(&tokens, tok);
			free(word);
		}
	}
	return (tokens);
}
