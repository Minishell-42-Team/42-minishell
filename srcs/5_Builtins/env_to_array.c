/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 16:30:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/23 16:30:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	count_envs(t_env_var *env_vars)
{
	int	count;

	count = 0;
	while (env_vars)
	{
		count++;
		env_vars = env_vars->next;
	}
	return (count);
}

char	**env_to_array(t_env_var *env_vars)
{
	char	**envp;
	int		size;
	int		i;
	char	*tmp;

	size = count_envs(env_vars);
	envp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env_vars)
	{
		tmp = ft_strjoin(env_vars->key, "=");
		envp[i] = ft_strjoin(tmp, env_vars->value);
		free(tmp);
		if (!envp[i])
			return (ft_free_table(&envp, size), NULL);
		env_vars = env_vars->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
