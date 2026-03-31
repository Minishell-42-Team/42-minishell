/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_buitins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:59:37 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/31 00:20:33 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_sbuiltin(t_command_ast *cmd, t_minishell_data **data)
{
	if (ft_strcmp(cmd->command, "env") == 0)
		return (ft_env((*data)->envs), 1);
	if (ft_strcmp(cmd->command, "exit") == 0)
		return (ft_exit(data), 1);
	return (0);
}
static int	ft_export_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	t_list	*args;

	if (ft_strcmp(cmd->command, "export") == 0)
	{
		if (!cmd->args)
			return (ft_export(NULL, &(*data)->envs, &(*data)->execdirs), 1);
		args = cmd->args;
		while (args)
		{
			ft_export((char *)args->content, &(*data)->envs,
					&(*data)->execdirs);
			args = args->next;
		}
		return (1);
	}
	return (0);
}

static int ft_unset_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	t_list	*args;

	if (ft_strcmp(cmd->command, "unset") == 0)
	{
		if (!cmd->args)
			return (ft_unset(&(*data)->envs, NULL), 1);
		args = cmd->args;
		while (args)
		{
			ft_unset(&(*data)->envs, (char *)args->content);
			args = args->next;
		}
		return (1);
	}
	return (0);
}


int exec_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	if (exec_sbuiltin(cmd, data) || ft_export_builtin(cmd, data)
			|| ft_unset_builtin(cmd, data))
		return (1);
	return (0);
}
