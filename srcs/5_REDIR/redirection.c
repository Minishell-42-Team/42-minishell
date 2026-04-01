/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:16:25 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/01 11:33:24 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_redir_file *redir)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_OUT)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redir->type == REDIR_IN)
		fd = open(redir->file, O_RDONLY);
	else if (redir->type == HEREDOC)
		fd = handle_heredoc(redir->file);
	if (fd < 0)
		perror(redir->file);
	return (fd);
}

static int	dup2_last_redir_in(t_redir_file *redir, int *fd)
{
	int	fd_close;

	if (!redir && *fd != STDIN_FILENO)
		return (dup2(*fd, STDIN_FILENO), 1);
	else if (!redir && *fd == STDIN_FILENO)
		return (1);
	else if (redir && redir->type != REDIR_IN)
		return (dup2_last_redir_in(redir->next, fd));
	else if (redir && redir->type == REDIR_IN)
	{
		*fd = open_file(redir);
		if (*fd < 0)
			return (0);
		fd_close = *fd;
	}
	if (dup2_last_redir_in(redir->next, fd))
		return (close(fd_close), 1);
	else
		return (close(fd_close), 0);
}

static int	dup2_last_redir_out(t_redir_file *redir, int *fd)
{
	int	fd_close;

	if (!redir && *fd != STDOUT_FILENO)
		return (dup2(*fd, STDOUT_FILENO), 1);
	if (!redir && *fd == STDOUT_FILENO)
		return (1);
	if (redir && redir->type != REDIR_OUT && redir->type != APPEND)
		return (dup2_last_redir_out(redir->next, fd));
	if (redir && (redir->type == APPEND || redir->type == REDIR_OUT))
	{
		*fd = open_file(redir);
		if (*fd < 0)
			return (0);
		fd_close = *fd;
	}
	if (dup2_last_redir_in(redir->next, fd))
		return (close(fd_close), 1);
	else
		return (close(fd_close), 0);
}

int	apply_redirections(t_redir_file *redirs)
{
	int	fd;

	if (!redirs)
		return (1);
	fd = STDIN_FILENO;
	if (!dup2_last_redir_in(redirs, &fd))
		return (0);
	fd = STDOUT_FILENO;
	if (!dup2_last_redir_out(redirs, &fd))
		return (0);
	return (1);
}
