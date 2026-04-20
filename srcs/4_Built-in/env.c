/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:28:04 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/20 13:14:17 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(t_env_var *envs)
{
	t_env_var	*node;

	node = envs;
	while (node)
	{
		if (node->value)
		{
			printf("%s=", node->key);
			printf("'%s'\n", node->value);
		}
		node = node->next;
	}
	return (0);
}
