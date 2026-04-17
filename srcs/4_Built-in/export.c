/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:57:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/16 17:40:38 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i] || (str[i] == '=' && (str[i + 1] == '"'
			|| str[i + 1] == '\'')))
		return (1);
	--i;
	while (str[++i])
		if (str[i] == '!')
			return (0);
	return (1);
}

static int	find_pos_equal(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	return (i);
}

static int	set_dir(char *dir, t_list **execdirs)
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
		return (0);
	return (ft_lstadd_back(execdirs, node), 1);
}

static int	get_execdirs(char *path, t_list **execdirs)
{
	char	**dirs;
	t_list	*node;
	int		i;

	if (!path)
		return (0);
	node = *execdirs;
	dirs = ft_split(path, ':');
	if (!dirs)
		return (0);
	i = -1;
	while (dirs[++i])
	{
		while (node && ft_strcmp(node->content, dirs[i]) != 0)
			node = node->next;
		if (!node)
			if (!set_dir(dirs[i], execdirs))
				return (ft_lstclear(execdirs, free), 0);
		node = *execdirs;
	}
	while (--i >= 0)
		free(dirs[i]);
	return (free(dirs), 1);
}

void	*ft_export(char *args, t_env_var **env_vars, t_list **execdirs)
{
	char	*items;
	int		pos;

	if (!args)
		return (print_env_vars(*env_vars), NULL);
	if (!is_valid_identifier(args))
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(args, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_status = 1;
		return (NULL);
	}
	items = ft_strdup(args);
	if (!items)
		return (NULL);
	pos = find_pos_equal(items);
	if (!items[pos])
		return (add_env_var(env_vars, items, NULL), free(items), NULL);
	items[pos] = '\0';
	if (ft_strcmp(items, "PATH") == 0)
		get_execdirs(items + pos + 1, execdirs);
	add_env_var(env_vars, items, items + pos + 1);
	g_status = 0;
	return (free(items), NULL);
}
