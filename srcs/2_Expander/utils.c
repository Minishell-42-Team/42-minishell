/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 02:00:00 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/08 02:00:00 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && quote == 0)
			quote = str[i++];
		else if (is_quote(str[i]) && quote == str[i])
		{
			quote = 0;
			i++;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

void	clean_quotes_command(t_command_ast *cmd)
{
	t_list			*arg_node;
	t_redir_file	*redir_node;
	char			*tmp;

	if (cmd->command)
	{
		tmp = remove_quotes(cmd->command);
		(free(cmd->command), cmd->command = tmp);
	}
	arg_node = cmd->args;
	while (arg_node)
	{
		tmp = remove_quotes((char *)arg_node->content);
		(free(arg_node->content), arg_node->content = tmp);
		arg_node = arg_node->next;
	}
	redir_node = cmd->redirs;
	while (redir_node)
	{
		if (redir_node->file)
		{
			tmp = remove_quotes(redir_node->file);
			(free(redir_node->file), redir_node->file = tmp);
		}
		redir_node = redir_node->next;
	}
}
