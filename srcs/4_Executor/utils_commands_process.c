/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:18:10 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/22 14:53:15 by vnaoussi         ###   ########.fr       */
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

int	check_built_parent(t_command_ast *cmd, t_minishell_data **data)
{
	int	stdin_save;
	int	stdout_save;
	int	ret;

	if (!cmd->command || (ft_strcmp(cmd->command, "export") != 0
			&& ft_strcmp(cmd->command, "unset") != 0
			&& ft_strcmp(cmd->command, "exit") != 0
			&& ft_strcmp(cmd->command, "cd") != 0))
		return (0);
	if (ft_strcmp(cmd->command, "exit") == 0)
		if (exec_builtin(cmd, data))
			return (1);
	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	if (!apply_redirections(cmd->redirs))
		return (restore_io(&stdin_save, &stdout_save), 1);
	clean_quotes_command(cmd);
	ret = exec_builtin(cmd, data);
	restore_io(&stdin_save, &stdout_save);
	if (ret == 2)
		ft_exit(cmd, data);
	return (1);
}
void	fork_child_do(t_command_ast *command, t_minishell_data **data)
{
	char	**args;
	char	**envp;
	int		len;
	int		stdin_save;

	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	stdin_save = dup(STDIN_FILENO);
	if (!apply_redirections(command->redirs))
		(dup2(stdin_save, STDIN_FILENO), ft_clean_all(data), exit(EXIT_FAILURE));
	if (!command->command)
		(dup2(stdin_save, STDIN_FILENO), ft_clean_all(data), exit(EXIT_SUCCESS));
	if (exec_builtin(command, data))
	{
		len = g_status;
		(ft_clean_all(data), exit(len));
	}
	args = get_args(command, data, &len);
	if (!args)
	{
		len = 127;
		if (is_dir(command->command))
			len = 126;
		(ft_clean_all(data), exit(len));
	}
	envp = env_to_array((*data)->envs);
	execve(args[0], args, envp);
	perror("execve");
	(ft_free_table(&args, len + 1),
		ft_free_table(&envp, len + 1), ft_clean_all(data), exit(127));
}

void	fork_parent_do(int *fd_in, t_command_ast *cmd, int p_in, int p_out)
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (cmd->next)
	{
		if (p_out != -1)
			close(p_out);
		*fd_in = p_in;
	}
	else if (p_in != -1)
		close(p_in);
}
