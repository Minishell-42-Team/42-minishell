/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:56:36 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/15 23:35:51 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (copy != NULL)
	{
		while (s[i++])
			copy[i - 1] = ((char *)s)[i - 1];
		copy[i - 1] = '\0';
	}
	return (copy);
}
