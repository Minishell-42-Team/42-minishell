/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:23:17 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 18:06:30 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sjoin = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (sjoin != NULL)
	{
		ft_strlcpy(sjoin, s1, s1_len + 1);
		ft_strlcpy(sjoin + s1_len, s2, s2_len + 1);
	}
	return (sjoin);
}
