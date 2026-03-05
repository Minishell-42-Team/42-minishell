/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 22:21:36 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/22 18:55:43 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_putnbrbase(long c, char *base)
{
	size_t	base_len;
	long	nb;
	int		len;

	len = 0;
	base_len = ft_strlen(base);
	if (base_len == 10 && c < 0)
	{
		ft_putchar('-');
		len++;
		nb = -1 * c;
	}
	else
		nb = c;
	ft_perfdivp((unsigned int)nb, base_len, base, &len);
	return (len);
}
