/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:59 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/13 16:31:46 by clwenhaj         ###   ########.fr       */
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
	while (i < len)
	{
		if ((*table)[i])
			free((*table)[i]);
		i++;
	}
	free(*table);
	*table = NULL;
}

void	handle_fork_signal(int sig)
{
	if (sig == SIGINT)
		printf("\n");
	else if (sig == SIGQUIT)
		printf("\n");
}
