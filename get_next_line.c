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
//
#include <stdio.h>

static	t_list	*new_file(t_list **file_list, int fd)
{
	t_list *tmp;

	tmp = *file_list;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("\0", 1);
	tmp->content_size = fd;
	ft_lstadd(file_list, tmp);
	tmp = *file_list;
	return (tmp);
}

static	void	gnl_cat(char **line, t_list *file)
{
	int		size_line;
	char	*tmp;

	size_line = ft_strclen(file->content, '\n');
	*line = ft_strsub(file->content, 0, size_line);
	if (((char *)(file->content))[size_line + 1] != '\0') //  size_line < (int)ft_strlen(file->content))
	{
		tmp = ft_strdup(file->content + (size_line + 1));
		free(file->content);
		file->content = tmp;
		//printf("file->content: %s\n", file->content);
	}
	else
		ft_strclr(file->content);
}

static	int		gnl_read(char **line, t_list *file, char *buf)
{
	int		num_bytes;
	char	*tmp;

	while ((num_bytes = read(file->content_size, buf, BUFF_SIZE)) > 0)
	{
		buf[num_bytes] = '\0';
		//printf("buf: %s\n", buf);
		if (!(tmp = ft_strjoin(file->content, buf)))
			return (-1);
		//printf("tmp: %s\n", tmp);
		free(file->content);
		//printf("tmp after free: %s\n", tmp);
		file->content = ft_strdup(tmp);
		free(tmp);
		//printf("file->content: %s\n", file->content);
		if (ft_strchr(buf, '\n'))
			break ;
		ft_strclr(buf);
	}
	//printf("tmp: %s\n", tmp);
	//printf("num_bytes: %d file->content: %s\n", num_bytes, file->content);
	if (num_bytes < BUFF_SIZE && !ft_strlen(file->content))
		return (0);
	gnl_cat(line, file);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static	t_list	*file_list;
	t_list			*file;
	int				i;

	if ((fd < 0 || !line || read(fd, 0, 0) < 0))
		return (-1);
	file = new_file(&file_list, fd);
	if ((i = gnl_read(line, file, buf)) == 0)
	{	
		ft_strclr(file->content);
		return (0);
	}
	//printf("%d\n", i);
	return (i);

}
