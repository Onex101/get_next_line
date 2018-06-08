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
		return (0);
	else if (j > 0)
	{
		node->read = i;
		if (node->buf)
		  	free(node->buf);
		if (i < BUFF_SIZE)
			node->buf = ft_strdup(buf);
		else
			node->buf = ft_strdup((ft_strchr(buf, '\n')) + 1);
		return (1);
	}
	return (0);
}

static	int	gnl_cat(char *buf, t_line *node)
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
			if (gnl_read(buf, node) == 0)
			node->read = 0;
			return (1);
		}
		ft_strcat(node->pnt, node->buf);
		ft_strclr(node->buf);
	}
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	t_line	*node;
	int				i;
	int				g_cat;
	int				g_read;

	i = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	if (!node)
	{
		node = (t_line *)ft_memalloc(sizeof(t_line));
		node->fd = fd;
		node->pnt = (char *)ft_memalloc(1000000);
	}
	ft_strclr(node->pnt);
	if (!line || !node || fd < 0)
		return (-1);
	*line = node->pnt;
	if ((g_cat = gnl_cat(buf, node)) == 1)
	{
		*line = ft_strdup(node->pnt);
		return (1);
	}
	g_read = gnl_read(buf, node);
	if (g_read == 0 && g_cat == 0)
	{
		*line = ft_strdup(node->pnt);
		return (0);
	}
	ft_strclr(node->pnt);
	return (1);
}
