/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xrhoda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 10:03:33 by xrhoda            #+#    #+#             */
/*   Updated: 2018/05/31 09:36:32 by xrhoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>	
#include <stdio.h>
#include "libft/libft.h"
#include "get_next_line.h"

static int gnl_cat(char *buf, char *pnt, a_list *node)
{
	int i;

	i = 0;
	if(node->buf)
	{
		if(ft_strchr(node->buf, '\n'))
			{
				ft_strcat(pnt, node->buf);
				*(ft_strchr(pnt, '\n')) = '\0';
				i = ft_strlen(pnt);
				ft_memcpy(pnt, node->buf, i);
				if (i < BUFF_SIZE)
				{
					ft_memcpy(buf, (node->buf + i) + 1, (BUFF_SIZE - i));
					ft_memcpy(node->buf, buf, BUFF_SIZE - i);
				}
				return (1);
			}
		ft_strcat(pnt, node->buf);
	}
	return (0);
}

static int gnl_read(char *pnt, char *buf, a_list *node)
{
	int i;

	i = 0;
	while ((i = read(node->fd, buf, BUFF_SIZE)) > 0)
	{
		ft_strcat(pnt, buf);
		if (ft_strchr(buf, '\n'))
			break;
		if (!(i < BUFF_SIZE))
			ft_bzero(buf, BUFF_SIZE);
	}
	if (i != 0)
	{
		*(ft_strchr(pnt, '\n')) = '\0';
		if (node->buf)
			free(node->buf);
 		node->buf = (char *)(char*)ft_memalloc(sizeof(char)*(BUFF_SIZE) + 1);
 		ft_memcpy(node->buf, ft_strchr(buf, '\n') + 1, ((BUFF_SIZE - ft_strclen(buf, '\n') + 1)));
		return (1);
 	}
	return (0);
}

int get_next_line(const int fd, char **line)
{
	char buf[BUFF_SIZE + 1];
	static a_list *node;
	char *pnt;
	int i;
	int g_cat;
	int g_read;

	i = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	pnt = (char *)ft_memalloc(BUFF_SIZE + 1 + 100);
	if (!pnt)
		return (-1);
	*line = pnt;
	if (!node)
		node = (a_list *)ft_memalloc(sizeof(a_list));
	if(!node)
		return(-1);
	node->fd = fd;
	if((g_cat = gnl_cat(buf, pnt, node)) == 1)
	{
		return (1);
	}
	g_read = gnl_read(pnt, buf, node);
	if (g_read == 0 && g_cat == 0)
	{
		ft_bzero(buf, BUFF_SIZE + 1);
		ft_bzero(node->buf, ft_strlen(node->buf));
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc == 1)
		fd = 0;
	else if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		return (2);
	while (get_next_line(fd, &line) == 1)
	{
		ft_putendl(line);
		free(line);
	}
	if (argc == 2)
		close(fd);
}
