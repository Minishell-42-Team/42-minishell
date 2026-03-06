/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:14:25 by vnaoussi          #+#    #+#             */
/*   Updated: 2025/11/19 17:26:49 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_gettriml(char const *s1, char const *set)
{
	size_t	i;
	size_t	nb;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	nb = len;
	while (ft_strchr(set, s1[i]) != NULL && i < len)
		i++;
	if (i != len)
		while (ft_strchr(set, s1[--nb]) != NULL)
			;
	if (i == len || len == 0)
		return (0);
	return (nb - i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*strtrim;
	size_t	trim_len;
	size_t	i;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	trim_len = ft_gettriml(s1, set);
	strtrim = (char *)malloc(sizeof(char) * (trim_len + 1));
	if (strtrim != NULL)
	{
		while (ft_strchr(set, s1[i]) != NULL && i < len)
			i++;
		if (i < len)
			ft_strlcpy(strtrim, s1 + i, trim_len + 1);
		else
			strtrim[0] = '\0';
	}
	return (strtrim);
}
