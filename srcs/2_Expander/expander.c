/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:33:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/21 16:34:00 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(const char *str, int *pos, t_env_var *env_vars)
{
	char	key[256];
	int		k;

	if (!str || !pos)
		return (ft_strdup(""));
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (ft_itoa(g_status));
	}
	k = 0;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
	{
		if (k < 255)
			key[k++] = str[*pos];
		(*pos)++;
	}
	key[k] = '\0';
	return (get_env_val(key, env_vars));
}

static void	update_quote(char c, char *quote)
{
	if (is_quote(c) && (*quote == 0 || *quote == c))
	{
		if (*quote == 0)
			*quote = c;
		else
			*quote = 0;
	}
}

static char	*process_dollar(char *str, int *i, t_env_var *envs)
{
	int	k;

	k = *i + 1;
	if (str[k] == '"' || str[k] == '\'')
		return (NULL);
	if (str[k] && (ft_isalnum(str[k]) || str[k] == '_' || str[k] == '?'))
	{
		*i = k;
		return (expand_variable(str, i, envs));
	}
	return (NULL);
}

static char	*handle_expansion(char *str, t_env_var *envs)
{
	char	*new_str;
	int		i;
	char	quote;
	char	*tmp;

	new_str = ft_strdup("");
	i = 0;
	quote = 0;
	while (str && str[i])
	{
		if (is_quote(str[i]) && (quote == 0 || quote == str[i]))
		{
			update_quote(str[i++], &quote);
			continue ;
		}
		tmp = NULL;
		if (str[i] == '$' && quote != '\'')
			tmp = process_dollar(str, &i, envs);
		if (tmp)
			new_str = ft_join_free(new_str, tmp);
		else
			new_str = ft_join_free(new_str, ft_substr(str, i++, 1));
	}
	return (new_str);
}

void	expander_tokens(t_token *tokens, t_env_var *envs)
{
	t_token	*curr;
	t_token	*prev;
	char	*expanded;

	curr = tokens;
	prev = NULL;
	while (curr)
	{
		if (curr->type == WORD && curr->value
			&& (!prev || prev->type != HEREDOC))
		{
			expanded = handle_expansion(curr->value, envs);
			free(curr->value);
			curr->value = expanded;
		}
		prev = curr;
		curr = curr->next;
	}
}
