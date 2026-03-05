/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 19:34:16 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/22 20:51:23 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static void	ft_printprec(unsigned long addr, int base_len, char *base, int *len)
{
	if (addr < (unsigned long)base_len)
		*len += ft_putchar(base[addr]);
	else
	{
		ft_printprec(addr / base_len, base_len, base, len);
		ft_printprec(addr % base_len, base_len, base, len);
	}
}

void	ft_printp(void *p, int *len)
{
	uintptr_t	addr;

	if (p == NULL)
	{
		*len += ft_putstr("(nil)");
		return ;
	}
	addr = (uintptr_t)p;
	*len += ft_putstr("0x");
	ft_printprec((unsigned long)addr, 16, "0123456789abcdef", len);
}
