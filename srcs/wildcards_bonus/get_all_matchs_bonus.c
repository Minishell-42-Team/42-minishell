/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_matchs_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:23:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/13 15:37:39 by clwenhaj         ###   ########.fr       */
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

static int	find_match(char *pattern, t_list **args, char *path, int *count);

static int	handle_match_logic(t_match_data *d, char *sp, struct dirent *e)
{
	if (sp && !is_p_dir(e->d_name))
	{
		*sp = '\0';
		if (is_dir(d->path) && ft_matched(d->pattern, e->d_name))
			if (!find_match(sp + 1, d->args, d->path, d->count))
				return (0);
		*sp = '/';
	}
	else if (!sp && ft_matched(d->pattern, e->d_name))
	{
		if (!is_p_dir(e->d_name) && !add_new_arg(d->args,
				d->path + 2, d->count))
			return (0);
	}
	return (1);
}

static int	find_match(char *pattern, t_list **args, char *path, int *count)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*slash_pos;
	int				len;
	t_match_data	d;

	dir = opendir(path);
	if (!dir)
		return (1);
	slash_pos = ft_strchr(pattern, '/');
	len = ft_strlen(path);
	d.args = args;
	d.count = count;
	d.path = path;
	d.pattern = pattern;
	entry = readdir(dir);
	while (entry)
	{
		get_pathname(path, entry->d_name);
		if (!handle_match_logic(&d, slash_pos, entry))
			return (closedir(dir), 0);
		ft_bzero(path + len, 255 - len);
		entry = readdir(dir);
	}
	return (closedir(dir), 1);
}

static int	process_wildcard(t_list *arg, t_list **args, char *path, int *count)
{
	char	*content;

	content = (char *)arg->content;
	if (ft_strchr(content, '*') && !has_quotes(content))
	{
		if (!find_match(content, args, path, count))
			return (0);
		if (*count == 0)
			add_new_arg(args, content, NULL);
	}
	else
		add_new_arg(args, content, NULL);
	return (1);
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
	while (arg)
	{
		ft_bzero(path, 255);
		path[0] = '.';
		count = 0;
		if (!process_wildcard(arg, &args, path, &count))
		{
			ft_lstclear(&args, free);
			return (0);
		}
		arg = arg->next;
	}
	ft_lstclear(&cmd->args, free);
	cmd->args = args;
	return (1);
}
