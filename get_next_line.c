/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obuksha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:00:11 by obuksha           #+#    #+#             */
/*   Updated: 2019/03/25 10:00:17 by obuksha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		delete_node(t_fdlist **head, int fd)
{
	t_fdlist	*node;
	t_fdlist	*prev;

	node = *head;
	prev = *head;
	while (node)
	{
		if (node->fd == fd)
		{
			free(node->buffer);
			if (node == *head)
			{
				*head = node->next;
			}
			else
			{
				prev->next = node->next;
			}
			free(node);
			break ;
		}
		prev = node;
		node = node->next;
	}
}

t_fdlist	*find_or_create(t_fdlist **list, const int fd)
{
	t_fdlist	*node;

	node = *list;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	if (!(node = (t_fdlist *)malloc(sizeof(t_fdlist))))
		return (0);
	node->fd = (unsigned int)fd;
	node->buffer = (char *)malloc(BUFF_SIZE + 1);
	if (!node->buffer)
	{
		free(node);
		return (0);
	}
	node->buffer[0] = '\0';
	node->next = *list;
	*list = node;
	return (node);
}

void		swap_join_del(char **str, char **buff)
{
	char	*tmp;

	tmp = *str;
	*str = ft_strjoin(*str, *buff);
	free(tmp);
}

char		*returnnl_storebuf(t_fdlist *current)
{
	char	*nlcplus;
	char	*readtextnl;
	char	*line;
	ssize_t	size;

	line = ft_strnew(0);
	while (!(nlcplus = ft_strchr(current->buffer, '\n')))
	{
		swap_join_del(&line, &current->buffer);
		current->buffer[0] = '\0';
		size = read(current->fd, current->buffer, BUFF_SIZE);
		if (size <= 0)
			return (line);
		current->buffer[size] = '\0';
	}
	readtextnl = ft_strsub(current->buffer, 0, nlcplus - current->buffer);
	swap_join_del(&line, &readtextnl);
	free(readtextnl);
	ft_memmove(current->buffer, nlcplus + 1, 1 + ft_strlen(nlcplus + 1));
	return (line);
}

int			get_next_line(const int fd, char **line)
{
	static t_fdlist		*head = NULL;
	t_fdlist			*cur;
	ssize_t				size;

	if (line == NULL || fd < 0 || !(cur = find_or_create(&head, fd)))
		return (-1);
	if (cur->buffer[0] == '\0')
	{
		size = read(fd, cur->buffer, BUFF_SIZE);
		if (size == -1)
		{
			delete_node(&head, fd);
			return (-1);
		}
		if (size == 0)
		{
			delete_node(&head, fd);
			return (0);
		}
		cur->buffer[size] = '\0';
	}
	*line = returnnl_storebuf(cur);
	if (cur->buffer[0] == '\0')
		delete_node(&head, fd);
	return (1);
}
