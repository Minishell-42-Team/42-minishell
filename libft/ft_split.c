/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:39:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 15:20:49 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	getlenword(char const *s, char c)
{
	int		n;
	int		i;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

static int	getlentword(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_free(char **splitw)
{
	int		i;

	i = 0;
	while (splitw[i] != NULL)
		free(splitw[i++]);
	free(splitw);
	return (NULL);
}

static char	**perform_split(char **array, const char *s, char c, int word_count)
{
	int		i;
	int		word_len;
	char	*pos;

	i = 0;
	pos = (char *)s;
	while (i < word_count)
	{
		while (*pos == c)
			pos++;
		word_len = getlentword(pos, c);
		array[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!array[i])
			return (ft_free(array));
		ft_strlcpy(array[i], pos, word_len + 1);
		pos += word_len;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**result_array;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = getlenword(s, c);
	result_array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result_array)
		return (NULL);
	return (perform_split(result_array, s, c, word_count));
}
