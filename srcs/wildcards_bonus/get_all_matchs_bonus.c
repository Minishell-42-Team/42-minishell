/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_matchs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:23:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/03 10:19:32 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	ft_matched(char *str_to_match, char *filename)
{
	if (!*str_to_match && !*filename)
		return (1);
	else if (*str_to_match == '*')
	{
		if (!*filename)
			return (1);
		if (!*(str_to_match + 1) && ft_matched(str_to_match, filename + 1))
			return (1);
		if (ft_matched(str_to_match + 1, filename + 1))
			return (1);
	}
	else if (*str_to_match == *filename)
		return (ft_matched(str_to_match + 1, filename + 1));
	return (0);
}

static int	find_match(char *str_to_match, t_list **args)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new;

	dir = opendir(".");
	entry = readdir(dir);
	if (!entry)
		return (printf("no matched found.\n"), 0);
	while (entry)
	{
		if (ft_matched(str_to_match, entry->d_name))
		{
			new = ft_lstnew(entry->d_name);
			if (!new)
				return (perror("malloc"), 0);
			ft_lstadd_back(args, new);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), 1);
}

int	get_matched_args(t_command_ast *cmd)
{
	t_list	*arg;
	t_list	*arg_to_free;
	t_list	*args;

	if (!cmd->args)
		return (1);
	arg = cmd->args;
	args = NULL;
	while (arg)
	{
		if (ft_strchr((char *)arg->content, '*'))
		{
			if (!find_match((char *)arg->content, &args))
				return (0);
			else
				(arg_to_free = arg, arg = arg->next,
				 ft_free_arg(&cmd->args, &arg_to_free));
		}
		else
			(ft_lstadd_back(&args, arg), arg = arg->next);
	}
	ft_lstclear(&cmd->args, free);
	cmd->args = args;
	return (1);
}
