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
	int		end_line;
	static	char stock[BUFF_SIZE];
	char	*temp;
	char	*add;

	i = 0;
	j = 0;
	line_ct = 0;
	end_line = 1;
	ft_putstr(stock);
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
	{
		i++;
		printf("i here is %d \n", i);
	}
	if (stock[i] == '\n')
	{
		if (!(*line = (char *)malloc(i + 1)))
			return (-1);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		return (1);
	}
	line_ct = i;
	if (!(temp = (char *)malloc(line_ct)))
		return (-1);
	temp = ft_strncpy(temp, (const char *)stock, i);
		//	printf("%s \n",temp);
	i = 0;
	j = 0;
	while (1)
	{
		//printf("test 00000000000000000\n");
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
		//	printf("333333333 here  \n");
		//	printf("%s \n", buff);
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			add = ft_strcpy (add, temp);
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			free(temp);
			free(buff);
			temp = add;
			//printf("%s \n",temp);
		}
		else
		{
			//ft_putendl(buff);
			//ft_putnbr(j);
			if (!(*line = (char *)malloc(line_ct + j + 1)))
				return (-1);
			//ft_putnbr(j);
			ft_putendl("here 6666666666666666");
			*line = ft_memmove (*line, temp, j);
			ft_putendl("here 5555555555555555");
			*line = ft_strncat(*line, (const char *)buff, j);
			ft_putendl(*line);
			free(temp);
			ft_bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 2), BUFF_SIZE - j - 1);
			free (temp);
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

	fd = 1;
	line = 0;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd ,line))
		ft_putstr(*line);
	return (0);
}

