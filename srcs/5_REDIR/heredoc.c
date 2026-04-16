/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:59:45 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/13 17:53:25 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_line(char *line, t_env_var *envs)
{
	char	*new_line;
	char	*tmp;
	char	*var_val;
	int		i;
	int		j;

	new_line = ft_strdup("");
	i = 0;
	while (line && line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1])
				|| line[i + 1] == '_' || line[i + 1] == '?'))
		{
			j = i + 1;
			var_val = expand_variable(line, &j, envs);
			if (!var_val)
				return (free(new_line), NULL);
			tmp = ft_strjoin(new_line, var_val);
			(free(new_line), free(var_val));
			if (!tmp)
				return (NULL);
			(new_line = tmp, i = j);
		}
		else
		{
			tmp = ft_calloc(2, sizeof(char));
			if (!tmp)
				return (free(new_line), NULL);
			(tmp[0] = line[i], var_val = ft_strjoin(new_line, tmp));
			(free(new_line), free(tmp));
			if (!var_val)
				return (NULL);
			(new_line = var_val, i++);
		}
	}
	return (free(line), new_line);
}

int	handle_heredoc(const char *delimiter, int quoted, t_env_var *envs)
{
	int		pipefd[2];
	char	*line;
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_IGN));
		close(pipefd[0]);
		while (1)
		{
			line = readline("> ");
			if (!line)
			{
				ft_putstr_fd("Minishell: warning: heredoc delimited by EOF\n", 2);
				(close(pipefd[1]), exit(0));
			}
			if (ft_strcmp(line, delimiter) == 0)
				(free(line), close(pipefd[1]), exit(0));
			if (!quoted)
				line = expand_line(line, envs);
			(write(pipefd[1], line, ft_strlen(line)),
				write(pipefd[1], "\n", 1), free(line));
		}
	}
	else
	{
		(close(pipefd[1]), waitpid(pid, &status, 0));
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			return (close(pipefd[0]), g_status = 130, -1);
		return (pipefd[0]);
	}
}
