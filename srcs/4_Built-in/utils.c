/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:42:55 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/01 14:41:47 by clwenhaj         ###   ########.fr       */
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

int	find_pos_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

int	set_dir(char *dir, t_list **execdirs)
{
	t_list	*node;
	char	*dir_c;
	int		len;

	len = ft_strlen(dir);
	dir_c = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dir_c)
		return (0);
	ft_strlcat(dir_c, dir, len + 1);
	node = ft_lstnew(dir_c);
	if (!node)
	{
		free(dir_c);
		return (0);
	}
	ft_lstadd_back(execdirs, node);
	return (1);
}
