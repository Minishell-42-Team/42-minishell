/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:59:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/17 16:52:22 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_line(char *line, t_heredoc *hd)
{
	if (!line)
	{
		ft_putstr_fd(ERR_HEREDOC, 2);
		close(hd->pipefd[1]);
		exit(0);
	}
	if (ft_strcmp(line, hd->delimiter) == 0)
	{
		free(line);
		close(hd->pipefd[1]);
		exit(0);
	}
	if (!hd->quoted)
		line = expand_line(line, hd->envs);
	write(hd->pipefd[1], line, ft_strlen(line));
	write(hd->pipefd[1], "\n", 1);
	free(line);
	return (0);
}

static void	child_heredoc(t_heredoc *hd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	close(hd->pipefd[0]);
	while (1)
	{
		line = readline("> ");
		handle_line(line, hd);
	}
}

int	handle_heredoc(const char *delimiter, int quoted, t_env_var *envs)
{
	t_heredoc	hd;
	pid_t		pid;
	int			status;

	if (pipe(hd.pipefd) == -1)
		return (perror("pipe"), -1);
	hd.delimiter = delimiter;
	hd.envs = envs;
	hd.quoted = quoted;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		child_heredoc(&hd);
	close(hd.pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(hd.pipefd[0]);
		g_status = 130;
		return (-1);
	}
	return (hd.pipefd[0]);
}
