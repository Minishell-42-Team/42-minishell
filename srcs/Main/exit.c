/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/10 16:02:17 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_command_ast command, t_minishell_data **data, int status)
{
	if (command && ft_lstsize(command->args) > 1)
		return (ft_putstr_fd("exit : trop d'arguments.\n", 2), 0);
	if (!command->args->content
			&& ft_isdigit((char *)command->args->content) != 1)
		return (ft_putstr_fd("Minishell : exit : ", 2),
				ft_putstr_fd((char *)node->content, 2),
					ft_putstr_fd("argument numérique nécessaire.\n", 2), 0);
	ft_free_command(&(*data)->cmds);
	free_tokens(&(*data)->tokens);
	ft_free_envs(&(*data)->envs);
	ft_lstclear(&(*data)->execdirs, free);
	free(*data);
	if (!command->args)
		exit(status);
	else
		exit((char)ft_itoa((char *)command-j>args));
}
