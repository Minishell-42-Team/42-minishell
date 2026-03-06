/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perfdivp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 17:26:34 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/22 20:46:22 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	ft_perfdivp(unsigned int c, size_t base_len, char *base, int *len)
{
	if (c < base_len)
	{
		ft_putchar(base[c]);
		*len += 1;
	}
	else
	{
		ft_perfdivp(c / base_len, base_len, base, len);
		ft_perfdivp(c % base_len, base_len, base, len);
	}
}
