/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:49:38 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 18:42:07 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

static void	dup2_close(int fd_in, t_command_ast *cmd, int pipfd_in,
		int pipfd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(fd_in);
	}
	if (cmd->next)
	{
		if (pipfd_in != -1)
			close(pipfd_in);
		if (pipfd_out != -1)
		{
			if (dup2(pipfd_out, STDOUT_FILENO) == -1)
				perror("dup2");
			close(pipfd_out);
		}
	}
	else
	{
		if (pipfd_in != -1)
			close(pipfd_in);
		if (pipfd_out != -1)
			close(pipfd_out);
	}
}

static int	init_bf_execute(t_command_ast *cmds, t_command_ast **cmd,
		pid_t **pids, int *fd_in)
{
	t_command_ast	*node;
	int				i;

	node = cmds;
	*cmd = cmds;
	*fd_in = STDIN_FILENO;
	i = 0;
	while (node)
	{
		if (cmds->next || (node->command
				&& !ft_check_builtin_must_not_fork(node->command)
				&& ft_strcmp(node->command, "cd") != 0) || !node->command)
			i++;
		node = node->next;
	}
	if (i == 0)
	{
		*pids = NULL;
		return (0);
	}
	*pids = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!*pids)
		return (-1);
	return (i);
}

static void	run_pipeline_loop(t_minishell_data **data, t_command_ast *cmd,
		pid_t *pids, int *fd_in)
{
	int	p[2];
	int	i;

	i = -1;
	while (cmd)
	{
		p[0] = -1;
		p[1] = -1;
		if (cmd->next && !set_pipe(p))
			return ;
		pids[++i] = fork();
		if (pids[i] == 0)
		{
			free(pids);
			dup2_close(*fd_in, cmd, p[0], p[1]);
			fork_child_do(cmd, data);
		}
		fork_parent_do(fd_in, cmd, p[0], p[1]);
		cmd = cmd->next;
	}
}

void	execute_pipeline(t_command_ast *cmds, t_minishell_data **data)
{
	int				fd_in;
	pid_t			*pids;
	t_command_ast	*cmd;

	if ((!cmds && !((*data)->tokens)) || (cmds && cmds->command
			&& ft_strcmp(cmds->command, "\\n") == 0 && !cmds->next))
		return ;
	if (!cmds || !prepare_heredoc(cmds, data))
		return ;
	ignore_signals();
	if (!cmds->next && check_built_parent(cmds, data))
		return ;
	if (init_bf_execute(cmds, &cmd, &pids, &fd_in) == -1)
		return ;
	fd_in = STDIN_FILENO;
	run_pipeline_loop(data, cmd, pids, &fd_in);
	ft_wait_child(cmds, pids);
	free(pids);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
