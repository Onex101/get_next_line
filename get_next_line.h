/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xrhoda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 09:27:02 by xrhoda            #+#    #+#             */
/*   Updated: 2018/05/31 08:15:26 by xrhoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE
#define BUFF_SIZE 1000
#include "./libft/libft.h"

typedef struct s_line
{
	int 	fd;
	char 	*pnt;
	char 	*buf;
	int 	read;
}			t_line;

int		get_next_line(const int fd, char **line);

#endif
