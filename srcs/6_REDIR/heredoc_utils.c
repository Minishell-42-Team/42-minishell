/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:59:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/17 16:51:17 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_var(char *new_line, char *line, int *i, t_env_var *envs)
{
	char	*tmp;
	char	*var_val;
	int		j;

	j = *i + 1;
	var_val = expand_variable(line, &j, envs);
	if (!var_val)
		return (free(new_line), NULL);
	tmp = ft_strjoin(new_line, var_val);
	free(new_line);
	free(var_val);
	if (!tmp)
		return (NULL);
	*i = j;
	return (tmp);
}

static char	*append_char(char *new_line, char c)
{
	char	*tmp;
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(new_line, buf);
	free(new_line);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static int	is_var(char *line, int i)
{
	if (line[i] == '$' && line[i + 1]
		&& (ft_isalnum(line[i + 1])
			|| line[i + 1] == '_' || line[i + 1] == '?'))
		return (1);
	return (0);
}

static char	*handle_append(char *new_line, char *line,
	int *i, t_env_var *envs)
{
	if (is_var(line, *i))
		return (append_var(new_line, line, i, envs));
	new_line = append_char(new_line, line[*i]);
	(*i)++;
	return (new_line);
}

char	*expand_line(char *line, t_env_var *envs)
{
	char	*new_line;
	int		i;

	new_line = ft_strdup("");
	i = 0;
	if (!new_line)
		return (NULL);
	while (line && line[i])
	{
		new_line = handle_append(new_line, line, &i, envs);
		if (!new_line)
			return (NULL);
	}
	return (free(line), new_line);
}
