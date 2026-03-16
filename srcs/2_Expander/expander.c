/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clwenhaj <clwenhaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 09:33:54 by clwenhaj          #+#    #+#             */
/*   Updated: 2026/03/16 15:12:10 by vnaoussi         ###   ########.fr       */
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

char    *expand_variable(const char *str, int *pos)
{
	char	key[256];
	int		k;
	char	*val;
	char	*value;

	if (str[*pos] == '?')
	{
		(*pos)++;
		val = ft_itoa(g_status);
		return (val);
	}
	k = 0;
	while (ft_isalnum(str[*pos]) || str[*pos] == '_')
	{
		if (k < 255)
			key[k++] = str[*pos];
		(*pos)++;
	}
	key[k] = '\0';
	value = getenv(key);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}
