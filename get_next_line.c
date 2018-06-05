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
#include <stdio.h>
#include "libft/libft.h"
#include "get_next_line.h"

static int overflow_cat(char *buf, char *pnt, a_list *node)
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
					printf("[%s]\n", pnt);
					return (0);
				}
				return (1);
			}
		else
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
	}
	if (i != 0)
	{
		*(ft_strchr(pnt, '\n')) = '\0';
		return (1);
 	}
 	else if (i == 0)
	{
		ft_strcat(pnt, buf);
	}
	return (0);
}

int get_next_line(int argc, char **line)
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
	if (!node)
		node = (a_list *)ft_memalloc(sizeof(a_list));
	if(!node)
		return(-1);
	if (!line[1])
		node->fd = 1;
	if((g_cat = overflow_cat(buf, pnt, node)) == 1)
	{
		return (1);
	}
	if (!node->fd)
		node->fd = open(line[1], O_RDONLY);
	g_read = gnl_read(pnt, buf, node);
	if (node->buf)
		free(node->buf);
	node->buf = (char *)(char*)ft_memalloc(sizeof(char)*(BUFF_SIZE) + 1);
	ft_memcpy(node->buf, ft_strchr(buf, '\n') + 1, ((BUFF_SIZE - ft_strclen(buf, '\n') + 1)));
	printf("[%s]\n", pnt);
	if (g_read == 0 && g_cat == 0)
	{
		free(node);
		ft_bzero(buf, BUFF_SIZE + 1);
		return (0);
	}
	return (1);
}

		
