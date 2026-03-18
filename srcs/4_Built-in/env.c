/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:28:04 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/03/18 13:32:12 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void    ft_env(t_env_var *envs)
{
    t_env_var   *node;

    node = envs;
    while (node)
    {
        if (node->value)
        {
            printf("%s=", node->key);
            printf("'%s'\n", node->value);
        }
        node = node->next;²
    }
}
