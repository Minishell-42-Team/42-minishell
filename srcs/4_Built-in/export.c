/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:57:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/18 14:14:31 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	find_pos_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (i != 0)
		return (i);
	return (-1);
}

void	*ft_export(char *args, t_env_var **env_vars)
{
	char	*items;
	int		pos;

	if (!args)
		return (print_env_vars(*env_vars), NULL);
	items = ft_strdup(args);
	if (!items)
		return (perror("error: An allocation fail."), NULL);
	pos = find_pos_equal(items);
	if (pos == -1)
	{
		perror("error: bad assignment.");
		return (free(items), NULL);
	}
	if (!items[pos])
		return (add_env_var(env_vars, items, NULL), free(items), NULL);
	items[pos] = '\0';
	add_env_var(env_vars, items, items + pos + 1);
	return (free(items), NULL);
}
