/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:33:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/13 15:35:09 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_val(const char *key, t_env_var *env_vars)
{
	t_env_var	*node;

	node = env_vars;
	while (node)
	{
		if (node->key && ft_strcmp(node->key, key) == 0)
		{
			if (node->value)
				return (ft_strdup(node->value));
			return (ft_strdup(""));
		}
		node = node->next;
	}
	return (ft_strdup(""));
}

static char	*ft_join_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	(free(s1), free(s2));
	return (res);
}

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

/*static char	*handle_expansion(char *str, t_env_var *envs)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	(new_str = ft_strdup(""), i = 0, quote = 0);
	while (str && str[i])
	{
		if (is_quote(str[i]) && (quote == 0 || quote == str[i]))
		{
			if (quote == 0)
				quote = str[i];
			else
				quote = 0;
		}
		if (str[i] == '$' && quote != '\'' && str[i + 1] && (ft_isalnum(str[i
						+ 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			j = i + 1;
			new_str = ft_join_free(new_str, expand_variable(str, &j, envs));
			i = j;
		}
		else
			new_str = ft_join_free(new_str, ft_substr(str, i++, 1));
	}
	return (new_str);
}*/

static char	*handle_expansion(char *str, t_env_var *envs)
{
	char	*new_str;
	int		i;
	int		j;
	int		k;
	char	quote;

	(new_str = ft_strdup(""), i = 0, quote = 0);
	while (str && str[i])
	{
		if (is_quote(str[i]) && (quote == 0 || quote == str[i]))
		{
			if (quote == 0)
				quote = str[i];
			else
				quote = 0;
			i++;
			continue ;
		}
		if (str[i] == '$' && quote != '\'')
		{
			k = i + 1;
			while (str[k] == '"' || str[k] == '\'')
				k++;

			if (str[k] && (ft_isalnum(str[k]) || str[k] == '_' || str[k] == '?'))
			{
				j = k;
				new_str = ft_join_free(new_str,
						expand_variable(str, &j, envs));
				i = j;
				continue ;
			}
		}
		new_str = ft_join_free(new_str, ft_substr(str, i, 1));
		i++;
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
