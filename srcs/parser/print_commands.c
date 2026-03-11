/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/10 15:32:15 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_command_ast *cmds)
{
	t_command_ast	*curr;
	t_list			*arg;
	t_redir_file	*redir;
	int				i;

	curr = cmds;
	i = 0;
	while (curr)
	{
		printf("\033[1;34m--- Command %d ---\033[0m\n", i++);
		printf("Command: %s\n", curr->command);
		printf("Args: ");
		arg = curr->args;
		while (arg)
		{
			printf("[%s] ", (char *)arg->content);
			arg = arg->next;
		}
		printf("\nRedirs: ");
		redir = curr->redirs;
		while (redir)
		{
			printf("(%s: %s) ", token_type_str(redir->type), redir->file);
			redir = redir->next;
		}
		printf("\n\n");
		curr = curr->next;
	}
}
