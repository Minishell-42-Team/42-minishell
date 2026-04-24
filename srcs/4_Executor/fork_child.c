/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:09:01 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/24 13:11:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_link_to_file(char *command, t_list *execdirs)
{
	char	*access_link;
	t_list	*node;
	int		len;

	if (ft_strchr(command, '/'))
		return (handle_relative_command(command));
	node = execdirs;
	while (node)
	{
		len = ft_strlen(command) + ft_strlen((char *)node->content) + 1;
		access_link = (char *)ft_calloc(len + 1, sizeof(char));
		if (!access_link)
			return (NULL);
		ft_strlcat(access_link, (const char *)node->content, len + 1);
		ft_strlcat(access_link, "/", len + 1);
		ft_strlcat(access_link, command, len + 1);
		if (access(access_link, F_OK) == 0 && access(access_link, X_OK) == 0)
			return (access_link);
		free(access_link);
		node = node->next;
	}
	return (NULL);
}

static char	**get_args(t_command_ast *command, t_minishell_data **data,
		int *len)
{
	char	*access_link;

	if (ft_strcmp(command->command, "") == 0)
		return (ft_putstr_fd("Minishell : : command not found\n", 2), NULL);
	access_link = get_link_to_file(command->command, (*data)->execdirs);
	if (!access_link && !is_dir(command->command))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command->command, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	if (!access_link)
		return (NULL);
	*len = ft_lstsize(command->args);
	return (fill_args(command, access_link, *len));
}

static void	handle_builtin_exit(t_minishell_data **data)
{
	int	len;

	len = g_status;
	ft_clean_all(data);
	exit(len);
}

static void	handle_no_args(t_command_ast *command, t_minishell_data **data)
{
	int	len;

	len = 127;
	if (is_dir(command->command))
		len = 126;
	ft_clean_all(data);
	exit(len);
}

void	fork_child_do(t_command_ast *command, t_minishell_data **data, int pid)
{
	char	**args;
	char	**envp;
	int		len;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!apply_redirections(command->redirs))
		(ft_clean_all(data), exit(EXIT_FAILURE));
	if (!command->command)
		(ft_clean_all(data), exit(EXIT_SUCCESS));
	if (exec_builtin(command, data, pid))
		handle_builtin_exit(data);
	args = get_args(command, data, &len);
	if (!args)
		handle_no_args(command, data);
	envp = env_to_array((*data)->envs);
	execve(args[0], args, envp);
	perror("execve");
	(ft_free_table(&args, len + 1),
		ft_free_table(&envp, len + 1), ft_clean_all(data), exit(127));
}
