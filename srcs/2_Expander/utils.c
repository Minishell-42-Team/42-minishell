/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 02:00:00 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/21 13:42:41 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_val(const char *key, t_env_var *env_vars)
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

char	*ft_join_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static void	clean_quotes_args(t_list *arg_node)
{
	char	*tmp;

	while (arg_node)
	{
		tmp = remove_quotes((char *)arg_node->content);
		free(arg_node->content);
		arg_node->content = tmp;
		arg_node = arg_node->next;
	}
}

static void	clean_quotes_redirs(t_redir_file *redir_node)
{
	char	*tmp;

	while (redir_node)
	{
		if (redir_node->file)
		{
			tmp = ft_strtrim(redir_node->file, "\'\"");
			free(redir_node->file);
			redir_node->file = tmp;
		}
		redir_node = redir_node->next;
	}
}

void	clean_quotes_command(t_command_ast *cmd)
{
	char	*tmp;

	if (cmd->command)
	{
		tmp = remove_quotes(cmd->command);
		free(cmd->command);
		cmd->command = tmp;
	}
	clean_quotes_args(cmd->args);
	clean_quotes_redirs(cmd->redirs);
}
