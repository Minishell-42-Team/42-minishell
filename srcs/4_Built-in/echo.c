/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 16:37:39 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/02 12:05:38 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_n_options(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_list *args)
{
	int	flag_newline;

	flag_newline = 1;
	while (args && is_n_options((char *)args->content))
	{
		flag_newline = 0;
		args = args->next;
	}
	while (args)
	{
		printf("%s", (char *)args->content);
		if (args->next)
			printf(" ");
		args = args->next;
	}
	if (flag_newline)
		printf("\n");
	g_status = 0;
}
