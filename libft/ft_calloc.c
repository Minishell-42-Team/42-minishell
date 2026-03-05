/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:43:04 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 18:05:24 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*mem;
	size_t	i;

	i = 0;
	if (size != 0 && n > SIZE_MAX / size)
		return ((void *) NULL);
	mem = malloc(n * size);
	if (mem != (void *) NULL)
	{
		while (i < n * size)
			((char *) mem)[i++] = 0;
	}
	return ((void *) mem);
}
