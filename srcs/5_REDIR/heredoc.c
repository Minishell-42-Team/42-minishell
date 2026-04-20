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

static char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	if (!s1 || !s2)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static char	*expand_line(char *line, t_env_var *envs)
{
	char	*new_line;
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
			new_line = join_and_free(new_line, expand_variable(line, &j, envs));
			i = j;
		}
		else
			new_line = join_and_free(new_line, ft_substr(line, i++, 1));
		if (!new_line)
			return (free(line), NULL);
	}
	free(line);
	return (new_line);
}

static void	heredoc_child(int pipefd_out, const char *delim, int q,
		t_minishell_data **data)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("Minishell: warning: ", 2);
			ft_putstr_fd("heredoc delimited by EOF\n", 2);
			close(pipefd_out);
			ft_clean_all(data);
			exit(0);
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			close(pipefd_out);
			ft_clean_all(data);
			exit(0);
		}
		if (!q)
			line = expand_line(line, (*data)->envs);
		ft_putendl_fd(line, pipefd_out);
		free(line);
	}
}

int	handle_heredoc(const char *delimiter, int quoted, t_minishell_data **data)
{
	int		pipefd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(pipefd[1], delimiter, quoted, data);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(pipefd[0]);
		g_status = 130;
		return (-1);
	}
	return (pipefd[0]);
}
