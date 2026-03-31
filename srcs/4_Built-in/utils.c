/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:42:55 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/30 13:58:55 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_check_builtin_must_not_fork(char *command)
{
	if (ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "export") == 0
			|| ft_strcmp(command, "exit") == 0)
		return (1);
	return (0);
}
