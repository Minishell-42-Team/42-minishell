/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:35:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/04/20 12:50:44 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env_var	*update_env(t_env_var *env, char *key, char *value)
{
	t_env_var	*tmp;
	t_env_var	*new;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (env);
		}
		tmp = tmp->next;
	}
	new = malloc(sizeof(t_env_var));
	if (!new)
		return (env);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = env;
	return (new);
}

int	ft_cd(char *args, t_env_var *envp)
{
	char	*oldpwd;
	char	*pwd;
	char	*home;

	home = NULL;
	if (!args)
	{
		home = getenv("HOME");
		if (!home)
			return (1);
		args = home;
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("getcwd"), 1);
	if (chdir(args) != 0)
		return (perror("cd"), free(oldpwd), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("getcwd"), free(oldpwd), 1);
	envp = update_env(envp, "PWD", pwd);
	envp = update_env(envp, "OLDPWD", oldpwd);
	return (free(oldpwd), free(pwd), 0);
}
