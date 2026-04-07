/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_matchs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:23:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/07 13:43:57 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	ft_matched(char *pattern, char *filename)
{
	if (!*pattern && !*filename)
		return (1);
	if (*pattern == '*')
	{
		if (ft_matched(pattern + 1, filename))
			return (1);
		if (*filename && ft_matched(pattern, filename + 1))
			return (1);
		return (0);
	}
	if (*filename && *pattern == *filename)
		return (ft_matched(pattern + 1, filename + 1));
	return (0);
}

static int	find_match(char *str_to_match, t_list **args, char *dir_current)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(dir_current);
	entry = readdir(dir);
	count = 0;
	if (!entry)
		return (perror("readdir"), 0);
	while (entry)
	{
		if (ft_matched(str_to_match, entry->d_name))
		{
			if (!add_new_arg(args, entry->d_name))
				return (closedir(dir), 0);
			count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count != 0);
}

int	get_matched_args(t_command_ast *cmd)
{
	t_list	*arg;
	t_list	*args;

	if (!cmd->args)
		return (1);
	arg = cmd->args;
	args = NULL;
	while (arg)
	{
		if (ft_strchr((char *)arg->content, '*'))
		{
			if (!find_match((char *)arg->content, &args, "."))
				return (printf("no matched found: %s.\n", (char *)arg->content),
						ft_lstclear(&args, free), 0);
		}
		else
			add_new_arg(&args, (char *)arg->content);
		arg = arg->next;
	}
	ft_lstclear(&cmd->args, free);
	cmd->args = args;
	return (1);
}
