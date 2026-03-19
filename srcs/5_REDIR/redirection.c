/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:16:25 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/19 14:09:27 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	apply_redirections(t_redir_file *redirs)
{
	int	fd;
	
	while (redirs)
	{
		if (redirs->type == REDIR_OUT)
		{
			fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redirs->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == APPEND)
		{
			fd = open(redirs->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror(redirs->file);
				return (-1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (redirs->type == REDIR_IN)
		{
			fd = open(redirs->file, O_RDONLY);
			if (fd < 0)
			{
				perror(redirs->file);
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (redirs->type == HEREDOC)
		{
			fd = handle_heredoc(redirs->file);
			if (fd < 0)
			{
				perror("heredoc");
				return (-1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		redirs = redirs->next;
	}
	return (0);
}
