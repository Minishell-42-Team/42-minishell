/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:18:10 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/20 11:35:47 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_link_to_file(char *command, t_list *execdirs)
{
	char	*access_link;
	t_list	*node;
	int		len;

	node = execdirs;
	while (node)
	{
		len = ft_strlen(command) + ft_strlen((char *)node->content);
		access_link = (char *)ft_calloc(len + 1, sizeof(char));
		if (!access_link)
			return (NULL);
		ft_strlcat(access_link, (const char *)node->content, len + 1);
		ft_strlcat(access_link, command, len + 1);
		if (access(access_link, F_OK) == 0 && access(access_link, X_OK) == 0)
			return (access_link);
		free(access_link);
		node = node->next;
	}
	return (NULL);
}

static int	apply_redirections(t_redir_file *redir)
{
	int fd;

	while (redir)
	{
		if (redir->type == REDIR_OUT)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == APPEND)
			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (redir->type == REDIR_IN)
			fd = open(redir->file, O_RDONLY);
		if (fd == -1)
			return (perror(redir->file), 0);
		if (redir->type == REDIR_IN)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir = redir->next;
	}
	return (1);
}

static void	fork_and_execute(char **args, t_command_ast *command)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (!apply_redirections(command->redirs))
			exit(EXIT_FAILURE);
		if (execve(args[0], args, NULL) == - 1)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		g_status = WEXITSTATUS(status);
	}
}

int	run_command(t_command_ast *command, t_minishell_data **data)
{
	char	**args;
	char	*access_link;
	t_list	*node;
	int		i;
	int		len;

	access_link = get_link_to_file(command->command, (*data)->execdirs);
	if (!access_link)
		return (printf("We cannot execute command.\n"), 0);
	i = 0;
	len = ft_lstsize(command->args);
	args = (char **)malloc(sizeof(char *) * (len + 2));
	if (!args)
		return (free(access_link), 0);
	args[0] = access_link;
	node = command->args;
	while (node)
	{
		args[++i] = (char *)node->content;
		node = node->next;
	}
	args[i + 1] = NULL;
	fork_and_execute(args, command);
	return (free(access_link), free(args), 1);
}
