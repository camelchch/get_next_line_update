/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/27 17:13:14 by saxiao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "get_next_line.h"
#include "libft/libft.h"

int		get_next_line(const int fd, char **line)
{
	int		i;
	int		j;
	int		line_ct;
	char	*buff;
	//int		end_line;
	static	char stock[BUFF_SIZE];
	char	*temp;
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	//end_line = 0;
	//ft_putstr(stock);
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
	{
		i++;
		printf("i here is %d \n", i);
	}
	if (stock[i] == '\n')
	{
		if (!(*line = (char *)malloc(i + 1)))
			return (-1);
		ft_bzero(*line, BUFF_SIZE);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		return (1);
	}
	line_ct = i;
	ft_putnbr(i);
	if (!(temp = (char *)malloc(line_ct)))
		return (-1);
	temp = ft_strncpy(temp, (const char *)stock, i);
	printf("here is temp %s \n",temp);
	i = 0;
	while (1)
	{
		j = 0;
		printf("test 00000000000000000\n");
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		i = read(fd, buff, BUFF_SIZE);
		ft_putendl(buff);
		if ( i == -1)
			return (-1);
		if (!i)
			return (0);
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		ft_putnbr(j);
		printf("333333333 here  \n");
		printf("buff =%s \n", buff);
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			add = ft_strcpy (add, temp);
			printf("test 1111 add =%s \n",add);
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			printf("test 2222 add =%s \n",add);
			free(temp);
			free(buff);
			temp = add;
			//	free (add);
			printf("temp =%s \n",temp);
		}
		else
		{
			printf("enter here or not ?? \n");
			printf("buff is =%s\n",buff);
			printf("line_ct is =%d\n", line_ct);
			printf("j =%d\n",j);

			line = (char **)malloc(sizeof(char *));
			*line = (char *)malloc(line_ct + j + 1);
			if (!*line)
				return (-1);
			ft_putnbr(j);
			//ft_putendl("here 6666666666666666");
			*line = ft_memmove (*line, temp, line_ct);
			printf("here 5555555555555555 *line =%s\n",*line);
			*line = ft_strncat(*line, (const char *)buff, j);
			ft_putendl(*line);
			ft_bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 1), BUFF_SIZE - j);
			
			printf("end temp =%s \n",temp);
			printf("end stock =%s \n",stock);
			return (1);
		}
	}
	return (0);
}

#include <fcntl.h>

int main(int ac, char **av)
{
	char **line;
	int		fd;
	(void) ac++;
	(void) av;

	//fd = 1;
	line = 0;
	fd = open(av[1], O_RDONLY);
	//write(1,"nihao\nhuhu\n\nsa\nlulu",20);
	while (get_next_line(fd ,line))
	{
		ft_putstr(*line);
		ft_putendl("");
		ft_putendl("above is in the main");
	}
	return (0);
}

