/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 11:35:09 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/23 19:07:56 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	update_env(t_env_var *env, char *key, char *value)
{
	t_env_var	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	update_cd_env(t_env_var *envp, char *oldpwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror("getcwd");
	else
	{
		update_env(envp, "OLDPWD", oldpwd);
		update_env(envp, "PWD", pwd);
		free(pwd);
	}
}

void	ft_cd(char *args, t_env_var *envp)
{
	char	*oldpwd;

	if (!args)
	{
		printf("cd: missing arguments\n");
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}
	if (chdir(args) != 0)
	{
		perror("cd");
		free(oldpwd);
		return ;
	}
	update_cd_env(envp, oldpwd);
	free(oldpwd);
}
