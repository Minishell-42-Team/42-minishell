/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 15:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/13 11:38:13 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args_and_redirs(t_command_ast *curr)
{
	t_list			*arg;
	t_redir_file	*redir;

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
}

void	print_commands(t_command_ast *cmds)
{
	t_command_ast	*curr;
	int				i;

	curr = cmds;
	i = 0;
	while (curr)
	{
		printf("\033[1;34m--- Command %d ---\033[0m\n", i++);
		printf("Command: %s\n", curr->command);
		print_args_and_redirs(curr);
		curr = curr->next;
	}
}
