/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 01:14:45 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 19:37:58 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	if_overlap(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 1;
	while (i < n)
		if ((char *)src + i++ == (char *)dest)
			return (i - 1);
	return (n);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	size_t	end_f;

	if (dest == NULL && src == NULL)
		return (NULL);
	end_f = if_overlap(dest, src, n);
	i = n;
	if (end_f > 0 && end_f < n)
		while (--i >= end_f)
			((char *)dest)[i] = ((char *)src)[i];
	ft_memcpy(dest, src, end_f);
	return (dest);
}
