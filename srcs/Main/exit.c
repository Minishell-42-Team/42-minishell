/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:03:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/18 02:21:47 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exit(t_minishell_data **data)
{
    ft_free_command(&(*data)->cmds);
    free_tokens((*data)->tokens);
    ft_free_envs(&(*data)->envs);
    free(*data);
    exit(EXIT_SUCCESS);
}
