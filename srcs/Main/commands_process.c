/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:49:38 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/30 15:45:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pipe(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		return (perror("pipe"), 0);
	return (1);
}

static void	dup2_close(int fd_in, t_command_ast *cmd, int pipfd_in,
		int pipfd_out)
{
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (cmd->next)
	{
		close(pipfd_in);
		dup2(pipfd_out, STDOUT_FILENO);
		close(pipfd_out);
	}
}

static void	ft_wait_child(t_command_ast *cmd, pid_t *pids)
{
	t_command_ast	*node;
	int				status;
	int				i;

	node = cmd;
	i = 0;
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
				g_status = 128 + WTERMSIG(status);
		}
		node = node->next;
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
		if (cmds->next)
			i++;
		else if (!ft_check_builtin_must_not_fork(node->command)
			&& ft_strcmp(node->command, "cd") != 0)
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

void	execute_pipeline(t_command_ast *cmds, t_minishell_data **data)
{
	int				pipefd[2];
	int				fd_in;
	pid_t			*pids;
	t_command_ast	*cmd;
	int				i;

	if (!cmds)
		return ;
	if (!cmds->next && check_built_parent(cmds, data))
		return ;
	if (init_bf_execute(cmds, &cmd, &pids, &fd_in) == -1)
		return ;
	i = -1;
	while (cmd)
	{
		if (cmd->next && !set_pipe(pipefd))
			return ;
		pids[++i] = fork();
		if (pids[i] == 0)
		{
			dup2_close(fd_in, cmd, pipefd[0], pipefd[1]);
			fork_child_do(cmd, data);
		}
		else
			fork_parent_do(&fd_in, cmd, pipefd[0], pipefd[1]);
		cmd = cmd->next;
	}
	(ft_wait_child(cmds, pids), free(pids));
}
