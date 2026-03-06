/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printarg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 02:18:39 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/22 20:50:20 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	ft_printarg(char format, va_list args, int *len)
{
	if (format == 'c')
		*len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		*len += ft_putstr(va_arg(args, char *));
	else if (format == 'p')
		ft_printp(va_arg(args, void *), len);
	else if (format == 'd')
		*len += ft_putnbrbase((long)va_arg(args, int), "0123456789");
	else if (format == 'i')
		*len += ft_putnbrbase((long)va_arg(args, int), "0123456789");
	else if (format == 'u')
		ft_perfdivp(va_arg(args, unsigned int), 10, "0123456789", len);
	else if (format == 'x')
		ft_perfdivp(va_arg(args, unsigned int), 16, "0123456789abcdef", len);
	else if (format == 'X')
		ft_perfdivp(va_arg(args, unsigned int), 16, "0123456789ABCDEF", len);
	else
		*len += ft_putchar(format);
}
