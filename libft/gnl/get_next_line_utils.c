/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:05:52 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/23 17:03:23 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

int	ft_gnl_free(char *buffer)
{
	free(buffer);
	return (1);
}

size_t	get_len_line(char *content_b)
{
	size_t	i;

	i = 0;
	if (!content_b)
		return (0);
	while (content_b[i] != '\n' && content_b[i])
		i++;
	if (content_b[i] == '\n')
		return (i + 1);
	return (i);
}

size_t	ft_strncat_l(char *dest, char *buffer, size_t len, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (dest == NULL || buffer == NULL)
		return (0);
	while (dest[i])
		i++;
	while (i + j < len && buffer[j] && buffer[j] != c)
	{
		dest[i + j] = buffer[j];
		j++;
	}
	if (buffer[j] == c && buffer[j])
		dest[i + j++] = c;
	dest[i + j] = '\0';
	return (j);
}

char	*init_fread(char *buffer, char *content_b, size_t size, char c)
{
	char	*content;

	if (!content_b && !buffer)
		return (NULL);
	content = (char *)malloc(sizeof(char) * (size + 1));
	if (content)
	{
		content[0] = '\0';
		if (content_b)
			ft_strncat_l(content, content_b, size, c);
		if (buffer)
			ft_strncat_l(content, buffer, size, c);
	}
	free(content_b);
	return (content);
}

int	read_and_save(int fd, char **content_b, size_t *size_content)
{
	char	*buffer;
	int		i;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	i = read(fd, buffer, BUFFER_SIZE);
	if (i == -1)
		return (!ft_gnl_free(buffer));
	while (i > 0)
	{
		buffer[i] = '\0';
		*size_content += i;
		*content_b = init_fread(buffer, *content_b, *size_content, '\0');
		if (buffer[0] && buffer[get_len_line(buffer) - 1] == '\n')
			return (ft_gnl_free(buffer));
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
			return (!ft_gnl_free(buffer));
	}
	free(buffer);
	return (1);
}
