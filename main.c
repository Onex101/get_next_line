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
	double time_spent;
     
    start = clock();
	int i;
	int fd = open("txt_files/gnl7_2.txt", O_RDONLY);
	char	**line;
	line = malloc(100000);
	*line = malloc(100000);
	i = 1;

	while ((i = get_next_line(fd, line)) > 0)
	{	
		printf("%d: Buff: {%d}  len: %zu [%s]\n",i ,BUFF_SIZE,ft_strlen(*line), *line);
	}
	 end = clock();
	

	time_spent = (double)(end - start) / CLOCKS_PER_SEC;
 	printf("%f\n",time_spent); 
	return(0);
}


