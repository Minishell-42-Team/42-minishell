/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 23:49:38 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/17 14:02:04 by clwenhaj         ###   ########.fr       */
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

static void	update_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		g_status = 128 + WTERMSIG(status);
		if (g_status == 131)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (g_status == 130)
			ft_putstr_fd("\n", 2);
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
			update_status(status);
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
		else if (node->command && !ft_check_builtin_must_not_fork(node->command)
			&& ft_strcmp(node->command, "cd") != 0)
			i++;
		else if (!node->command)
			i++;
		node = node->next;
	}
	if (i == 0)
		return (*pids = NULL, 0);
	*pids = (pid_t *)malloc(sizeof(pid_t) * i);
	if (!*pids)
		return (-1);
	return (i);
}

static int	prepare_heredoc(t_command_ast *cmds, t_env_var *envs)
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

void	execute_pipeline(t_command_ast *cmds, t_minishell_data **data)
{
	int				pipefd[2];
	int				fd_in;
	pid_t			*pids;
	t_command_ast	*cmd;
	int				i;

	if (!cmds || !prepare_heredoc(cmds, (*data)->envs))
		return ;
	(signal(SIGINT, SIG_IGN), signal(SIGQUIT, SIG_IGN));
	if (!cmds->next && check_built_parent(cmds, data))
		return ;
	if (init_bf_execute(cmds, &cmd, &pids, &fd_in) == -1)
		return ;
	i = -1;
	fd_in = STDIN_FILENO;
	while (cmd)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		if (cmd->next && !set_pipe(pipefd))
		{
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			free(pids);
			return ;
		}
		pids[++i] = fork();
		if (pids[i] < 0)
		{
			if (cmd->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			free(pids);
			return ;
		}
		if (pids[i] == 0)
			(dup2_close(fd_in, cmd, pipefd[0], pipefd[1]),
				fork_child_do(cmd, data));
		else
			fork_parent_do(&fd_in, cmd, pipefd[0], pipefd[1]);
		cmd = cmd->next;
	}
	ft_wait_child(cmds, pids);
	free(pids);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}
