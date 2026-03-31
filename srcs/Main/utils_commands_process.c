/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:18:10 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/31 00:13:16 by vnaoussi         ###   ########.fr       */
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
	char	**args;
	char	*access_link;
	t_list	*node;
	int		i;

	access_link = get_link_to_file(command->command, (*data)->execdirs);
	if (!access_link)
		return (printf("Minishell: %s: command not found\n", command->command), NULL);
	i = 0;
	*len = ft_lstsize(command->args);
	args = (char **)malloc(sizeof(char *) * (*len + 2));
	if (!args)
		return (free(access_link), NULL);
	args[0] = access_link;
	node = command->args;
	while (node)
	{
		args[++i] = (char *)node->content;
		node = node->next;
	}
	args[i + 1] = NULL;
	return (args);
}

int	check_built_parent(t_command_ast *cmd, t_minishell_data **data)
{
	int	stdin_save;
	int	stdout_save;

	if (ft_strcmp(cmd->command, "export") != 0 && ft_strcmp(cmd->command,
		"unset") != 0 && ft_strcmp(cmd->command, "exit") != 0
			&& ft_strcmp(cmd->command, "cd") != 0)
		return (0);
	stdin_save = dup(STDIN_FILENO);
	stdout_save = dup(STDOUT_FILENO);
	if (!apply_redirections(cmd->redirs))
	{
		dup2(stdin_save, STDIN_FILENO);
		dup2(stdout_save, STDOUT_FILENO);
		close(stdin_save);
		close(stdout_save);
		return (1);
	}
	exec_builtin(cmd, data);
	dup2(stdin_save, STDIN_FILENO);
	dup2(stdout_save, STDOUT_FILENO);
	close(stdin_save);
	close(stdout_save);
	return (1);
}

void	fork_child_do(t_command_ast *command, t_minishell_data **data)
{
	char	**args;
	char	**envp;
	int		len;

	if (!apply_redirections(command->redirs))
		exit(EXIT_FAILURE);
	if (exec_builtin(command, data))
		exit(g_status);
	args = get_args(command, data, &len);
	if (!args)
		exit(127);
	envp = env_to_array((*data)->envs);
	if (execve(args[0], args, envp) == -1)
		perror("execve");
	ft_free_table(&args, len);
	ft_free_table(&envp, ft_lstsize((t_list *)(*data)->envs));
	exit(EXIT_FAILURE);
}

void	fork_parent_do(int *fd_in, t_command_ast *command, int pipefd_in,
		int pipefd_out)
{
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	if (command->next)
	{
		close(pipefd_out);
		*fd_in = pipefd_in;
	}
}
