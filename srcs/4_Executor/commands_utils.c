/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 16:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 16:49:20 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sig_status(int status)
{
	g_status = 128 + WTERMSIG(status);
	if (g_status == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (g_status == 130)
		ft_putstr_fd("\n", 2);
}

void	ft_wait_child(t_command_ast *cmd, pid_t *pids)
{
	t_command_ast	*node;
	int				status;
	int				i;

	node = cmd;
	i = 0;
	status = 0;
	if (!pids)
		return ;
	while (node)
	{
		waitpid(pids[i++], &status, 0);
		if (!node->next)
		{
			if (WIFEXITED(status))
				g_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				handle_sig_status(status);
		}
		node = node->next;
	}
}

int	prepare_heredoc(t_command_ast *cmds, t_env_var *envs)
{
	t_command_ast	*cmd;
	t_redir_file	*redir;

	cmd = cmds;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == HEREDOC)
			{
				redir->heredoc_fd = handle_heredoc(redir->file,
						redir->quoted, envs);
				if (redir->heredoc_fd < 0)
					return (g_status = 130, 0);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	exec_simple_builtin_2(t_command_ast *cmd)
{
	if (ft_strcmp(cmd->command, ":") == 0)
	{
		g_status = 0;
		return (1);
	}
	if (ft_strcmp(cmd->command, "!") == 0)
	{
		g_status = 1;
		return (1);
	}
	return (0);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
