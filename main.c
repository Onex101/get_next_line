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
		node = (a_list *)ft_memalloc(sizeof(a_list)); // Create a node if one doesnt exist
	if (!argv[1])
		node->fd = 1; // If an text file isnt given read from standard in
	if (!node->fd)
		node->fd = open(argv[1], O_RDONLY); // If a text file is given open it and save fd to struct
	pnt = (char *)ft_memalloc(1); // Create a return pointer
	if (!pnt)
		return (-1); // Check if it exists else return an error
	if (node->buf)
		ft_strcat(pnt, node->buf); // If there is still a buf from the previous function call, concatinate into the new return point
	while ( (i = read(node->fd, buf, BUFF_SIZE)) > 0) // Start the read
	{
		ft_strcat(pnt, buf);	//Concatenate into reutn buf
		if (ft_strchr(buf, '\n')) //if there is a '\n' char break out of the loop
			break;
		ft_bzero(buf, BUFF_SIZE + 1); // overwrite the buff with zeros
	}
	if (i != 0)
		*(ft_strchr(pnt, '\n')) = '\0'; //if there were bytes read, put a null at the newline char
	if (node->buf)
		free(node->buf); //if a remainder buf already exists free it
	node->buf = (char *)(char*)ft_memalloc(sizeof(char)*(BUFF_SIZE) + 1);
	ft_memcpy(node->buf, ft_strrchr(buf, '\n') + 1, BUFF_SIZE + 1); //create a new remainder buff
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


