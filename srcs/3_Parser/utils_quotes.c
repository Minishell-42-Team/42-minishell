/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/21 13:52:10 by clwenhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*res;
	char	quote[2];

	if (!str)
		return (NULL);
	quote[0] = 0;
	quote[1] = 0;
	if (str[0] == '"' || str[0] == '\'')
		quote[0] = str[0];
	if (quote[0])
		res = ft_strtrim(str, quote);
	else
		res = ft_strdup(str);
	return (res);
}
