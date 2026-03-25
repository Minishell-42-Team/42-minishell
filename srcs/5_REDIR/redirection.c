/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:16:25 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/20 12:35:12 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_redir_file *redir)
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

int	apply_redirections(t_redir_file *redirs)
{
	int	fd;

	while (redirs)
	{
		fd = open_file(redirs);
		if (fd < 0)
			return (0);
		if (redirs->type == REDIR_OUT || redirs->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
		redirs = redirs->next;
	}
	return (1);
}
