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

// #include <fcntl.h>
// #include "get_next_line.h"

// int		main(int argc, char **argv)
// {
// 	int		fd;
// 	char	*line;

// 	if (argc == 1)
// 		fd = 0;
// 	else if (argc == 2)
// 		fd = open(argv[1], O_RDONLY);
// 	else
// 		return (2);
// 	while (get_next_line(fd, &line) == 1)
// 	{
// 		ft_putstr("PRINTING LINE...\n");
// 		ft_putendl(line);
// 		//free(line);
// 	}
// 	if (argc == 2)
// 		close(fd);
// }











#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
     

int	main()
{

	 clock_t start, end;
     
     start = clock();
	int i;
	int fd = open("bb.txt", O_RDONLY);
	char	**line;
	line = (char **)malloc(sizeof(char *));
	//*line = (char *)malloc(1);
	i = 1;
	while (get_next_line(fd, line) == 1)
	{	
		printf("%d : len : %zu [%s]\n",i ,ft_strlen(*line), *line);
		free(*line);

	}
	 end = clock();
	printf("%lu\n",end );

     // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

}
