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

static	int	gnl_read(char **pnt, char *buf, t_line *node)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while ((i = read(node->fd, buf, BUFF_SIZE)) > 0)
	{
		j++;
		if (ft_strchr(buf, '\n'))
		{
			*pnt = ft_strjoin(*pnt, buf);

			// ft_putstr("Point = ");
			// ft_putstr(*pnt);
			// ft_putstr("\n");
			break ;
		}
		*pnt = ft_strjoin(*pnt, buf);
		if (!(i < BUFF_SIZE))
			ft_bzero(buf, BUFF_SIZE);
	}
	if (i == 0 && j == 1)
		return (0);
	else if (j > 0)
	{
		node->read = i;
		if (node->buf)
		 	free(node->buf);
		node->buf = ft_strdup(ft_strchr(buf, '\n') + 1);
		// ft_putstr("Node->buf = ");
		// ft_putstr(node->buf);
		// ft_putstr("\n");
		return (1);
	}
	return (0);
}

static	int	gnl_cat(char **pnt, char *buf, t_line *node)
{
	char *tmp;

	if (node->buf)
	{
		tmp = *pnt;
		if (ft_strchr(node->buf, '\n'))
		{
			*pnt = ft_strjoin(tmp, ft_strcdup(node->buf, '\n'));
			free (tmp);
			node->buf = ft_strdup(ft_strchr(node->buf, '\n') + 1);
			return (1);
		}
		else if (node->read && node->read < BUFF_SIZE)
		{
			*pnt = ft_strdup(node->buf);
			gnl_read( pnt, buf, node);
			node->read = 0;
			return (1);
		}
		*pnt = ft_strdup(node->buf);
		free (tmp);
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
	*line = ft_memalloc(1);
	if (!node)
	{
		//ft_putstr("Created node\n");
		node = (t_line *)ft_memalloc(sizeof(t_line));
		node->fd = fd;
	}
	if (!node || fd < 0)
		return (-1);
	//ft_putstr("ENTERING GNL CAT\n");
	if ((g_cat = gnl_cat(line, buf, node)) == 1)
	{
		//ft_putstr("g_cat retruning one\n");
		return (1);
	}
	//ft_putstr("EXIT GNL CAT\n");
	//ft_putstr("ENTERING GNL READ\n");
	g_read = gnl_read(line, buf, node);
	if (g_read == 0 && g_cat == 0)
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		ft_bzero(node->buf, ft_strlen(node->buf));
		return (0);
	}
	return (1);
}
