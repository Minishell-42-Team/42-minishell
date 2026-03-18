/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 17:04:15 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/18 14:19:02 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_free_envs(t_env_var **env_vars)
{
	t_env_var	*node;

	node = *env_vars;
	while (node)
	{
		*env_vars = (*env_vars)->next;
		free(node);
		node = *env_vars;
	}
}

void	print_env_vars(t_env_var *env_var)
{
	t_env_var	*node;

	node = env_var;
	while (node)
	{
		printf("%s=", node->key);
		if (node->value)
			printf("'%s'\n", node->value);
		else
			printf("''\n");
		node = node->next;
	}
}

static int	check_if_exit_and_replace(t_env_var *head, char *key,
		char *value)
{
	t_env_var	*node;

	node = head;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
		{
			free(node->value);
			if (value)
				node->value = ft_strdup(value);
			else
				node->value = NULL;
			return (1);
		}
		node = node->next;
	}
	return (0);
}

static void	insert_env_var(t_env_var **head, t_env_var *node)
{
	t_env_var	*previous_node;

	previous_node = *head;
	if (!previous_node || ft_strcmp(previous_node->key, node->key) >= 0)
	{
		node->next = previous_node;
		*head = node;
		return ;
	}
	while (previous_node->next
		&& ft_strcmp(previous_node->next->key, node->key) < 0)
		previous_node = previous_node->next;
	node->next = previous_node->next;
	previous_node->next = node;
}

void	add_env_var(t_env_var **head, char *key, char *value)
{
	t_env_var	*node;

	if (!head || !key)
		return ;
	if (check_if_exit_and_replace(*head, key, value))
		return ;
	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		return ;
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return ;
	}
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	insert_env_var(head, node);
}
