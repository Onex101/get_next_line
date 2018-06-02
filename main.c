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

int ft_pro_gnl(int argc, char **argv)
{
	char buf[BUFF_SIZE + 1];
	static a_list *node;
	char *pnt;
	int i;

	ft_bzero(buf, BUFF_SIZE + 1);
	if (!node)
		node = (a_list *)ft_memalloc(sizeof(a_list));
	if (!argv[1])
		node->fd = 1; 
	if (!node->fd)
		node->fd = open(argv[1], O_RDONLY);
	pnt = (char *)ft_memalloc(1);
	if (!pnt)
		return (-1);
	if (node->buf)
		ft_strcat(pnt, node->buf);
	while ( (i = read(node->fd, buf, BUFF_SIZE)) > 0)
	{
		ft_strcat(pnt, buf);
		if (ft_strchr(buf, '\n'))
			break;
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (i != 0)
		*(ft_strrchr(pnt, '\n')) = '\0';
	if (node->buf)
		free(node->buf);
	node->buf = ft_strdup(ft_strchr(buf, '\n') + 1);
	printf("[%s]\n", pnt);
	free(pnt);
	return (0);
}

int main(int argc, char **argv)
{
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);

	return (0);
}


