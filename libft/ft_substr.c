/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:05:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/12 19:29:46 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_min(size_t n, size_t m)
{
	if (n < m)
		return (n);
	return (m);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	substr_len;

	if ((size_t)start > ft_strlen(s))
	{
		substr = (char *)malloc(sizeof(char) * 1);
		if (substr != NULL)
			substr[0] = '\0';
		return (substr);
	}
	substr_len = ft_min(len, ft_strlen(s) - (size_t)start);
	substr = (char *)malloc(sizeof(char) * (substr_len + 1));
	if (substr != NULL)
		ft_strlcpy(substr, s + start, substr_len + 1);
	return (substr);
}
