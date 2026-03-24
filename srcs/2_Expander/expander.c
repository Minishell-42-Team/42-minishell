/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:33:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/23 18:55:48 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// expand_variable sert à remplacer une variable d’environnement dans une chaîne
// Elle lit une variable à partir de str à la position pos,
// récupère sa valeur et la retourne sous forme de chaîne.
// *pos: pointeur qui permet de modifier la position pendant la lecture.
// $? correspond au code de retour de la dernière commande dans un shell
// getenv retourne un pointeur interne qu'il ne faut pas modifier.
// Donc on crée une copie sécurisée.

#include "minishell.h"

char	*expand_variable(const char *str, int *pos, t_env_var *env_vars)
{
	char		key[256];
	int			k;
	t_env_var	*node;

	if (!str || !pos)
		return (ft_strdup(""));
	if (str[*pos] == '?')
	{
		(*pos)++;
		return (ft_itoa(g_status));
	}
	k = 0;
	while (str[*pos] && (ft_isalnum(str[*pos]) || str[*pos] == '_'))
	{
		if (k < 255)
			key[k++] = str[*pos];
		(*pos)++;
	}
	key[k] = '\0';
	node = env_vars;
	while (node)
	{
		if (node->key && ft_strcmp(node->key, key) == 0)
		{
			if (node->value)
				return (ft_strdup(node->value));
			else
				return (ft_strdup(""));
		}
		node = node->next;
	}
	return (ft_strdup(""));
}
