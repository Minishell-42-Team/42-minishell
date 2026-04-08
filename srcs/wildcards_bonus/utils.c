/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 09:56:46 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/08 01:20:30 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_new_arg(t_list **args, char *content, int *count)
{
	t_list	*new;
	char	*data;

	data = ft_strdup(content);
	if (!data)
		return (0);
	new = ft_lstnew(data);
	if (!new)
		return (perror("malloc"), 0);
	ft_lstadd_back(args, new);
	if (count)
		*count = *count + 1;
	return (1);
}

int	is_dir(const char *path)
{
	struct	stat	info;

	if (stat(path, &info) != 0)
		return (0);
	return (S_ISDIR(info.st_mode));
}


void	get_pathname(char *path, const char *entry)
{
	ft_strlcat(path, "/", 255);
	ft_strlcat(path, entry, 255);
}
