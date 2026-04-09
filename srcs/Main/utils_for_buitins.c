/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_buitins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:59:37 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/07 00:15:58 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_simple_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	if (ft_strcmp(cmd->command, "env") == 0)
		return (ft_env((*data)->envs), 1);
	if (ft_strcmp(cmd->command, "echo") == 0)
		return (ft_echo(cmd->args), 1);
	if (ft_strcmp(cmd->command, "pwd") == 0)
		return (ft_pwd(), 1);
	if (ft_strcmp(cmd->command, "exit") == 0)
		return (ft_exit(data), 1);
	if (ft_strcmp(cmd->command, ":") == 0)
		return (g_status = 0, 1);
	if (ft_strcmp(cmd->command, "!") == 0)
		return (g_status = 1, 1);
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

static int	ft_unset_builtin(t_command_ast *cmd, t_minishell_data **data)
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

static int	ft_cd_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	char	*arg;

	if (ft_strcmp(cmd->command, "cd") == 0)
	{
		arg = NULL;
		if (cmd->args)
			arg = (char *)cmd->args->content;
		ft_cd(arg, (*data)->envs);
		return (1);
	}
	return (0);
}

int	exec_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	if (!cmd || !cmd->command)
		return (0);
	if (exec_simple_builtin(cmd, data)
		|| ft_export_builtin(cmd, data)
		|| ft_unset_builtin(cmd, data)
		|| ft_cd_builtin(cmd, data))
		return (1);
	return (0);
}
