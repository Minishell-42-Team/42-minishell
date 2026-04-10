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

void	ft_exit(t_minishell_data **data)
{
	ft_free_command(&(*data)->cmds);
	free_tokens(&(*data)->tokens);
	ft_free_envs(&(*data)->envs);
	ft_lstclear(&(*data)->execdirs, free);
	free(*data);
	exit(EXIT_SUCCESS);
}
