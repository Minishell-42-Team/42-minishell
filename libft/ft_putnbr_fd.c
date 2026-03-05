/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 20:09:08 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 18:53:57 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_putpnb_fd(int n, int fd)
{
	if (n < 10 && n >= 0)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putpnb_fd(n / 10, fd);
		ft_putpnb_fd(n % 10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	t_min;

	t_min = 0;
	if (n < 0)
	{
		if (n == INT_MIN)
		{
			n = n / 10;
			t_min = 1;
		}
		n = -1 * n;
		write(fd, "-", 1);
	}
	ft_putpnb_fd(n, fd);
	if (t_min)
		ft_putchar_fd('8', fd);
}
