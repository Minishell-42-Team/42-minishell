/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_for_buitins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:59:37 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 16:02:40 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_simple_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	if (ft_strcmp(cmd->command, "env") == 0)
	{
		g_status = ft_env((*data)->envs);
		return (1);
	}
	if (ft_strcmp(cmd->command, "echo") == 0)
	{
		g_status = ft_echo(cmd->args);
		return (1);
	}
	if (ft_strcmp(cmd->command, "pwd") == 0)
	{
		g_status = ft_pwd();
		return (1);
	}
	if (ft_strcmp(cmd->command, "exit") == 0)
	{
		g_status = ft_exit(cmd, data);
		return (1);
	}
	return (0);
}

static int	ft_export_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	t_list	*args;

	if (ft_strcmp(cmd->command, "export") == 0)
	{
		if (!cmd->args)
		{
			g_status = ft_export(NULL, &(*data)->envs, &(*data)->execdirs);
			return (1);
		}
		args = cmd->args;
		while (args)
		{
			g_status = ft_export((char *)args->content, &(*data)->envs,
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
		{
			g_status = ft_unset(&(*data)->envs, NULL);
			return (1);
		}
		args = cmd->args;
		while (args)
		{
			g_status = ft_unset(&(*data)->envs, (char *)args->content);
			args = args->next;
		}
		return (1);
	}
	return (0);
}

static int	ft_cd_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	char	*arg;

	arg = NULL;
	if (ft_strcmp(cmd->command, "cd") == 0)
	{
		if (cmd->args)
			arg = (char *)cmd->args->content;
		g_status = ft_cd(arg, (*data)->envs);
		return (1);
	}
	return (0);
}

int	exec_builtin(t_command_ast *cmd, t_minishell_data **data)
{
	if (!cmd || !cmd->command)
		return (0);
	if (exec_simple_builtin(cmd, data)
		|| exec_simple_builtin_2(cmd)
		|| ft_export_builtin(cmd, data)
		|| ft_unset_builtin(cmd, data)
		|| ft_cd_builtin(cmd, data))
		return (1);
	return (0);
}
