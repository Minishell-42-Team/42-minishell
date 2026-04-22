/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 15:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/22 14:22:39 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_relative_command(char *command)
{
	if (is_dir(command))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		return (NULL);
	}
	if (access(command, X_OK) == 0)
		return (ft_strdup(command));
	return (NULL);
}

char	**fill_args(t_command_ast *command, char *access_link, int len)
{
	char	**args;
	t_list	*node;
	int		i;

	args = (char **)malloc(sizeof(char *) * (len + 2));
	if (!args)
		return (free(access_link), NULL);
	args[0] = access_link;
	node = command->args;
	i = 0;
	while (node)
	{
		args[i + 1] = ft_strdup((char *)node->content);
		if (!args[i + 1])
		{
			ft_free_table(&args, i + 1);
			return (NULL);
		}
		node = node->next;
		i++;
	}
	args[i + 1] = NULL;
	return (args);
}

void	restore_io(int *stdin_save, int *stdout_save)
{
	dup2(*stdin_save, STDIN_FILENO);
	dup2(*stdout_save, STDOUT_FILENO);
	close(*stdin_save);
	close(*stdout_save);
}
