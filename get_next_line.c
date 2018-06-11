/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xrhoda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 09:26:44 by xrhoda            #+#    #+#             */
/*   Updated: 2018/05/31 07:55:47 by xrhoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static	int	gnl_read(char *buf, t_line *node)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((i = read(node->fd, buf, BUFF_SIZE)) > 0)
	{
		j++;
		ft_strcat(node->pnt, buf);
		if (ft_strchr(buf, '\n'))
		{
			*ft_strchr(node->pnt, '\n') = '\0';
			break ;
		}
		if (!(i < BUFF_SIZE))
			ft_strclr(buf);
	}
	if (i == 0 && j == 1)
		return (1);
	else if (j > 0 && buf)
	{
		node->read = i;
		if (node->buf)
			free(node->buf);
		if (ft_strchr(buf, '\n'))
			node->buf = ft_strdup((ft_strchr(buf, '\n')) + 1);
		else
			node->buf = ft_strdup(buf);
		ft_strclr(buf);
		return (1);
	}
	return (0);
}

static	int	gnl_cat(t_line *node)
{
	if (node->buf)
	{
		if (ft_strchr(node->buf, '\n'))
		{
			ft_strncat(node->pnt, node->buf, ft_strclen(node->buf, '\n'));
			node->buf = ft_strdup(ft_strchr(node->buf, '\n') + 1);
			return (1);
		}
		else if (node->read && node->read < BUFF_SIZE)
		{
			ft_strcat(node->pnt, node->buf);
			node->read = 0;
			return (1);
		}
		ft_strcat(node->pnt, node->buf);
		ft_strclr(node->buf);
	}
	return (0);
}

static	int new_node(const int fd, t_line **node)
{
	if (!*node)
	{
		*node = (t_line *)ft_memalloc(sizeof(t_line));
		if (!*node)
			return (-1);
		(*node)->fd = fd;
		(*node)->pnt = (char *)ft_memalloc(1000000);
		if (!(*node)->pnt)
			return (-1);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	t_line	*node;
	int				i;
	int				g_cat;

	i = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	if (!line || fd < 0 || (read(fd, 0, 0) == -1))
		return (-1);
	if (new_node(fd, &node) == -1)
		return (-1);
	ft_strclr(node->pnt);
	*line = node->pnt;
	if ((g_cat = gnl_cat(node)) == 1)
		return (1);
	if (gnl_read(buf, node) == 0 && g_cat == 0)
	{
		return (0);
	}
	return (1);
}
