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
//#include "get_next_line.h"

int ft_pro_gnl(int argc, char **argv)
{
	char buf[13];	
	int fd;
	char *pnt;

	ft_bzero(buf, 13);
	fd = open(argv[1], O_RDONLY);
	pnt = (char *)ft_memalloc(1);
	if (!pnt)
		return (-1);
	while (read(fd, buf, 12) > 0)
	{
		ft_strcat(pnt, buf);
		if (ft_strchr(buf, '\n'))
			break;
		ft_bzero(buf, 12);
	}
	*(ft_strrchr(pnt, '\n')) = '\0';
	printf("[%s]\n", pnt);
	free(pnt);
	return (0);
}

int main(int argc, char **argv)
{
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	ft_pro_gnl(argc, argv);
	return (0);
}


