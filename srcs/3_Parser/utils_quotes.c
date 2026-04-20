/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:00:00 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote_char(char *str, int *idx, char *quote, char *res)
{
	if ((str[idx[0]] == '\'' || str[idx[0]] == '"') && *quote == 0)
	{
		*quote = str[idx[0]];
		idx[0]++;
	}
	else if (str[idx[0]] == *quote)
	{
		*quote = 0;
		idx[0]++;
	}
	else
	{
		res[idx[1]] = str[idx[0]];
		idx[1]++;
		idx[0]++;
	}
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		idx[2];
	char	quote;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	idx[0] = 0;
	idx[1] = 0;
	quote = 0;
	while (str[idx[0]])
		handle_quote_char(str, idx, &quote, res);
	res[idx[1]] = '\0';
	return (res);
}
