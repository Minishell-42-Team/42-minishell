/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:59 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/23 15:54:25 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quit_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}

void	ft_free(void **nptr)
{
	free(*nptr);
	*nptr = NULL;
}

void	ft_free_table(char ***table, int len)
{
	int	i;

	if (!table || !*table)
		return ;
	i = 0;
	while (i <= len)
	{
		if ((*table)[i])
			free((*table)[i]);
		i++;
	}
	free(*table);
	*table = NULL;
}
