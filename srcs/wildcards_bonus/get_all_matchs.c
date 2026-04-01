/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_all_matchs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:23:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/01 01:02:02 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static int	ft_matched(char *str_to_match, char *filename)
{
	if (!*str_to_match && !*filename)
		return (1);
	if (*str_to_match == "*" && *(filename + 1) != *(str_to_match + 1))
		return (ft_matched(str_to_match, filename + 1));
	if (*str_to_match == *filename)
		return (ft_matched(str_to_match + 1, str_to_match + 1);
}
static int	find_match_remove(char *str_to_match, t_command_ast *cmd)
{
	DIR				*dir;
	struct dirent	*entry;
	t_list			*new;

	dir = opendir(".");
	entry = readdir(dir);
	if (!entry)
		retrun(printf("no matched found.\n"), 0);
	while (entry)
	{
		if (ft_matched(str_to_match, entry->d_name))
		{
			new = ft_lstnew(entry->d_name);
			if (!new)
				return (perror("malloc"), 0);
			ft_lstadd_front(&cmd->args, new);
		}
		entry = readdir(dir);
	}
	return (closedir(dir), 1);
}

int	get_matched_args(t_command_ast *cmd)
{
	char	*str_to_match;
	t_list	*arg;

	if (!cmd->args)
		return ;
	arg = cmd->args;
	while (str)
	{
		if (ft_strchr((char *)arg->content, '*'))
		{
			str_to_match = (char *)arg->content;
			if (!find_match_remove(str_to_match, cmd))
				return (0);
		}
		str = str->next;
	}
}
