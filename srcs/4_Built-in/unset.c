/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 14:49:21 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/17 15:21:05 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	check_env_and_del(t_env_var *env, char *key)
{
	if (ft_strcmp(env->key, key) == 0)
	{
		free(env->key);
		free(env->value);
		return (1);
	}
	return (0);
}

void	ft_unset(t_env_var **envs, char *key)
{
	t_env_var	*node;
	t_env_var	*save_node;

	node = *envs;
	save_node = *envs;
	if (check_env_and_del(node, key))
	{
		*envs = (*envs)->next;
		free(node);
		return ;
	}
	node = node->next;
	while (node)
	{
		if (check_env_and_del(node, key))
		{
			save_node->next = node->next;
			free(node);
			return ;
		}
		save_node = save_node->next;
		node = node->next;
	}
}
