/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/03 11:56:41 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
static int	ft_is_onlydigit(char *str)
{
	int i;

	if (!str)
		return (0);
	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int	ft_exit(t_command_ast *cmd, t_minishell_data **data)
{
	if (cmd && ft_lstsize(cmd->args) > 1)
		return (ft_putstr_fd("exit: too many arguments.\n", 2), g_status = 1, 0);
	if (cmd->args && ft_is_onlydigit((char *)cmd->args->content) != 1)
		return (ft_putstr_fd("exit: non numeric arguments.\n", 2), g_status = 1, 0);
	ft_free_command(&(*data)->cmds);
	free_tokens(&(*data)->tokens);
	ft_free_envs(&(*data)->envs);
	ft_lstclear(&(*data)->execdirs, free);
	free(*data);
	g_status = 0;
	if (cmd->args)
		g_status = ft_atoi((char *)cmd->args->content) % 250;
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
