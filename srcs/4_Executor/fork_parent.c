/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:18:10 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/22 16:33:34 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		restore_io(&stdin_save, &stdout_save);
		return (1);
	}
	clean_quotes_command(cmd);
	ret = exec_builtin(cmd, data);
	restore_io(&stdin_save, &stdout_save);
	if (ret == 2)
		ft_exit(cmd, data);
	return (1);
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
