/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:08:18 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 19:39:25 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	last_pos;

	i = 0;
	last_pos = 0;
	while (s[i])
		if (s[i++] == (char)c)
			last_pos = i;
	if ((char)c == 0)
		return ((char *)s + i);
	if (last_pos > 0)
		return ((char *)s + last_pos - 1);
	return (0);
}
