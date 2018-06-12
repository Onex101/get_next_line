/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xrhoda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 13:11:58 by xrhoda            #+#    #+#             */
/*   Updated: 2018/06/12 13:12:02 by xrhoda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "get_next_line.h"

static	t_list	*new_file(t_list **file, int fd)
{
	*file = ft_lstnew("\0", fd);
	return (*file);
}

int			get_next_line(const int fd, char **line)
{
	char	buf[BUFF_SIZE + 1];
	static	t_list *file;
	char	*pnt;
	int		num_bytes;
	int		size_line;

	if ((fd < 0 || !line || read(fd, 0, 0) < 0))
		return (-1);
	if (!file)
		file = new_file(&file, fd); // Multiple file descriptors
	if(!(pnt = ft_strnew(1)))
		return (-1);
	while ((num_bytes = read(file->content_size, buf, BUFF_SIZE)) > 0)
	{
		buf[num_bytes] = '\0';
		if (!(file->content = ft_strjoin(file->content, buf)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (num_bytes < BUFF_SIZE && !ft_strlen(file->content))
		return (0);
	size_line = ft_strclen(file->content, '\n');
	*line = ft_strsub(file->content, 0, size_line);
	if (size_line < ft_strlen(file->content))
		file->content += (size_line + 1);
	else
		ft_strclr(file->content);
	return (1);
}