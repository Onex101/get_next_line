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

	i = 0;
	ft_bzero(buf, BUFF_SIZE + 1);
	if (!node)
		node = (a_list *)ft_memalloc(sizeof(a_list)); // Create a node if one doesnt exist
	if (!argv[1])
		node->fd = 1; // If an text file isnt given read from standard in
	pnt = (char *)ft_memalloc(BUFF_SIZE + 1 + 100); // Create a return pointer
	if (!pnt)
		return (-1); // Check if it exists else return an error
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
				return(0);
			}
		}
		else
			ft_strcat(pnt, node->buf);
		//printf("[Overflow: %s] [pnt contains: %s]\n", node->buf, pnt);
	} // If there is still a buf from the previous function call, concatinate into the new return point

	if (!node->fd)
		node->fd = open(argv[1], O_RDONLY);
	while ((i = read(node->fd, buf, BUFF_SIZE)) > 0) // Start the read
	{
		ft_strcat(pnt, buf);	//Concatenate into return buf
		if (ft_strchr(buf, '\n')) //if there is a '\n' char break out of the loop
			break;
		ft_bzero(buf, BUFF_SIZE + 1); // overwrite the buff with zeros
	}
	if (i == 0)
	{
		ft_strcat(pnt, buf);
		//printf("[pnt contains: %s]\n", pnt);
	}
	else if (i != 0)
	{
		*(ft_strchr(pnt, '\n')) = '\0';
		if (node->buf)
		{
		free(node->buf);
		//ft_putstr("free success\n"); //if a remainder buf already exists free it
		}
		node->buf = (char *)(char*)ft_memalloc(sizeof(char)*(BUFF_SIZE) + 1);
		ft_memcpy(node->buf, ft_strchr(buf, '\n') + 1, ((BUFF_SIZE - ft_strclen(buf, '\n') + 1))); //create a new remainder buff
 	}
 //if there were bytes read, put a null at the newline char
	
	//ft_putstr("node buff malloc assigned\n");
	//ft_putstr("memcpy success\n");
	ft_putstr(pnt);
	ft_putstr("\n");
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

// BUFF_SIZE = 10;

// if (buf is not empty)
// 	r = strlen(buf)
// else
// 	r = read(); == 4
// while (r > 0)
// {
// 	...
// 	r = read();
// 	if (buf >= 0)
// 		buf[r] = 0
// }
// if ()
// 	return (1);

// return (r);

// read(fd, buf, BUFF_SIZE) == 0;


