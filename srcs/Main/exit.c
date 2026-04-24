/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/24 12:18:05 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_onlydigit(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_clean_all(t_minishell_data **data)
{
	if (!data || !*data)
		return ;
	ft_free_command(&(*data)->cmds);
	free_tokens(&(*data)->tokens);
	ft_free_envs(&(*data)->envs);
	ft_lstclear(&(*data)->execdirs, free);
	free(*data);
	*data = NULL;
}

int	ft_exit(t_command_ast *cmd, t_minishell_data **data, int pid)
{
	if (cmd && ft_lstsize(cmd->args) > 1)
		return (ft_putstr_fd("exit: too many arguments.\n", 2), 1);
	if (cmd->args && ft_is_onlydigit((char *)cmd->args->content) != 1)
	{
		if (pid > 0)
			printf("exit\n");
		ft_putstr_fd("exit: non numeric arguments.\n", 2);
		ft_clean_all(data);
		exit(2);
	}
	if (cmd->args)
		g_status = ft_atoi((char *)cmd->args->content) % 256;
	if (pid > 0)
		printf("exit\n");
	ft_clean_all(data);
	exit(g_status);
}
