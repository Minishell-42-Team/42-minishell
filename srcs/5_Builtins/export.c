/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 12:57:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 13:08:50 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (!str[i] || (str[i] == '=' && (str[i + 1] == '"'
				|| str[i + 1] == '\'')))
		return (1);
	while (str[i])
	{
		if (str[i] == '!')
			return (0);
		i++;
	}
	return (1);
}

static int	get_execdirs(char *path, t_list **execdirs)
{
	char	**dirs;
	int		i;

	if (!path)
		return (0);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (0);
	i = -1;
	while (dirs[++i])
	{
		if (!set_dir(dirs[i], execdirs))
		{
			while (dirs[i])
				free(dirs[i++]);
			free(dirs);
			ft_lstclear(execdirs, free);
			return (0);
		}
	}
	i = -1;
	while (dirs[++i])
		free(dirs[i]);
	free(dirs);
	return (1);
}

static void	print_export_error(char *args)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(args, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static void	update_export_var(char *items, int pos, t_env_var **env_vars,
		t_list **execdirs)
{
	items[pos] = '\0';
	if (ft_strcmp(items, "PATH") == 0)
		get_execdirs(items + pos + 1, execdirs);
	add_env_var(env_vars, items, items + pos + 1);
}

int	ft_export(char *args, t_env_var **env_vars, t_list **execdirs)
{
	char	*items;
	int		pos;

	if (!args)
		return (print_env_vars(*env_vars), 0);
	if (!is_valid_identifier(args))
		return (print_export_error(args), 1);
	items = ft_strdup(args);
	if (!items)
		return (1);
	pos = find_pos_equal(items);
	if (!items[pos])
		add_env_var(env_vars, items, NULL);
	else
		update_export_var(items, pos, env_vars, execdirs);
	free(items);
	return (0);
}
