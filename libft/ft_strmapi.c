/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 21:48:16 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 18:50:37 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*results;

	i = 0;
	results = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (results != NULL)
	{
		while (s[i++])
			results[i - 1] = f(i - 1, s[i - 1]);
		results[i - 1] = '\0';
	}
	return (results);
}
