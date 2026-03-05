/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:47:02 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/14 18:45:48 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
		if (s[i++] == (char)c)
			return ((char *)s + i - 1);
	if ((char)c == 0)
		return ((char *)s + i);
	return (0);
}
