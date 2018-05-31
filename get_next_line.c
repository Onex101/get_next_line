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

#include "get_next_line.h"

int	get_next_line(const int fd, char **line)
{
	int i; //index into line
	int j; // index into buffer
	*line = (char *)malloc(52000 * sizeof(char))
	static char buf[1000][BUFF_SIZE];
	int ret;

	while (ret = read(fd, buf[fd], BUFF_SIZE))
	{
		while()
			if ()
				ajkdshfajksdfhakjsdhfkjasdf
				return
		if ()
			ajkdshfajksdfhakjsdhfkjasdf
			return;

	}
	if (!line)
		return (-1);
}
