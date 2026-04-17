/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_matchs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:23:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/17 14:10:17 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	is_p_dir(char *path)
{
	return (ft_strcmp(path, "..") == 0 || ft_strcmp(path, ".") == 0);
}

static int	find_match(char *pattern, t_list **args, char *path, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*slash_pos;
	int				len;

	dir = opendir(path);
	entry = readdir(dir);
	slash_pos = ft_strchr(pattern, '/');
	len = ft_strlen(path);
	while (entry)
	{
		get_pathname(path, entry->d_name);
		if (slash_pos && !is_p_dir(entry->d_name))
		{
			*slash_pos = '\0';
			if (is_dir(path) && ft_matched(pattern, entry->d_name))
				if (!find_match(slash_pos + 1, args, path, count))
					return (closedir(dir), 0);
			*slash_pos = '/';
		}
		else if (!slash_pos && ft_matched(pattern, entry->d_name))
			if (!is_p_dir(entry->d_name) && !add_new_arg(args, path + 2, count))
				return (closedir(dir), 0);
		(ft_bzero(path + len, 255 - len), entry = readdir(dir));
	}
	return (closedir(dir), 1);
}

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

int	get_matched_args(t_command_ast *cmd)
{
	t_list	*arg;
	t_list	*args;
	char	path[255];
	int		count;

	if (!cmd->args)
		return (1);
	arg = cmd->args;
	args = NULL;
	ft_bzero(path, 255);
	count = 0;
	path[0] = '.';
	while (arg)
	{
		if (ft_strchr((char *)arg->content, '*')
			&& !has_quotes((char *)arg->content))
		{
			if (!find_match((char *)arg->content, &args, path, &count))
				return (ft_lstclear(&args, free), 0);
			if (count == 0)
				add_new_arg(&args, (char *)arg->content, NULL);
		}
		else
			add_new_arg(&args, (char *)arg->content, NULL);
		arg = arg->next;
		count = 0;
	}
	return (ft_lstclear(&cmd->args, free), cmd->args = args, 1);
}
