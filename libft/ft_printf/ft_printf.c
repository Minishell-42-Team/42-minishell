/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 21:03:31 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/23 18:00:29 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static int	is_validf(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_strchr("cspdiuxX%", str[i++ + 1]) == NULL)
			return (0);
		if (str[i])
			i++;
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	len = 0;
	i = 0;
	va_start(args, str);
	if (!is_validf(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
			ft_printarg(str[i++ + 1], args, &len);
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return ((int)len);
}
