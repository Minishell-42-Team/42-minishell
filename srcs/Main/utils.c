/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 15:45:59 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/13 15:48:13 by vnaoussi         ###   ########.fr       */
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
