/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnaoussi <vnaoussi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 23:01:06 by vnaoussi          #+#    #+#             */
/*   Updated: 2026/01/23 17:02:02 by vnaoussi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

static char	*ft_strdup_trim(char *content_b, char *rest)
{
	char	*line;
	size_t	len;
	int		i;

	if (!content_b || !rest)
		return (NULL);
	len = get_len_line(content_b);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[0] = '\0';
	i = ft_strncat_l(line, content_b, len, '\n');
	rest[0] = '\0';
	ft_strncat_l(rest, content_b + i, BUFFER_SIZE, '\0');
	free(content_b);
	return (line);
}

static char	*iscmplonrest(char *rest, size_t *size_c)
{
	int		size;
	char	*content;
	int		i;

	size = get_len_line(rest);
	content = NULL;
	if (size > 0 && rest[size - 1] == '\n')
	{
		content = init_fread(rest, NULL, size, '\n');
		i = size;
		while (i < BUFFER_SIZE)
		{
			rest[i - size] = rest[i];
			i++;
		}
		while (i <= BUFFER_SIZE)
			rest[i++] = '\0';
	}
	*size_c = size;
	return (content);
}

static t_gnl_list	*get_node(t_gnl_list **head, int fd)
{
	t_gnl_list	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_gnl_list *)malloc(sizeof(t_gnl_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->rest[0] = '\0';
	node->next = *head;
	*head = node;
	return (node);
}

static void	del_node(t_gnl_list **head, int fd)
{
	t_gnl_list	*current;
	t_gnl_list	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	char				*content_b;
	static t_gnl_list	*head;
	t_gnl_list			*node;
	size_t				size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = get_node(&head, fd);
	if (!node)
		return (NULL);
	content_b = iscmplonrest(node->rest, &size);
	if (content_b)
		return (content_b);
	content_b = (char *)malloc(sizeof(char) * (size + 1));
	if (!content_b)
		return (del_node(&head, fd), NULL);
	content_b[0] = '\0';
	size = ft_strncat_l(content_b, node->rest, size, '\0');
	if (!read_and_save(fd, &content_b, &size))
		return (del_node(&head, fd), ft_gnl_free(content_b), NULL);
	if (!content_b[0])
		return (del_node(&head, fd), ft_gnl_free(content_b), NULL);
	content_b = ft_strdup_trim(content_b, node->rest);
	return (content_b);
}
