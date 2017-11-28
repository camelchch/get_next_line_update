/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saxiao <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 01:27:08 by saxiao            #+#    #+#             */
/*   Updated: 2017/11/28 09:59:32 by saxiao           ###   ########.fr       */
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
	if (!(line = (char **)malloc(sizeof(char *))))
		return (-1);
	printf("   222222222222222 %s\n",stock);
	while (i < BUFF_SIZE && stock[i] && stock[i] != '\n')
		i++;
	printf("i here =%d\n",i);
	if (stock[i] == '\n')
	{
		if (!(*line = (char *)malloc(i + 1)))
			return (-1);
		ft_bzero(*line, BUFF_SIZE);
		*line = ft_strncpy(*line, stock, i);
		while (i + 1 < BUFF_SIZE)
			stock[j++] = stock[i++ + 1];
		printf("line here=%s\n",*line);
		return (1);
	}
	line_ct = i;
	printf("i2222 here =%d\n",i);
	if (!line_ct)
	{
		if (!(temp = (char *)malloc(line_ct)))
			return (-1);
		temp = ft_strncpy(temp, (const char *)stock, i);
		i = 0;
	}
	while (1)
	{
		j = 0;
		if (!(buff = (char *)malloc(BUFF_SIZE)))
			return (-1);
		i = read(fd, buff, BUFF_SIZE);
		printf("i 33333 here=%d\n",i);
		if ( i == -1)
			return (-1);
		if (!i)
		{
			printf("i is 0 here 55555");
			*line = (char *)malloc(line_ct + j + 1);
			*line = ft_memmove (*line, temp, line_ct);
			return (0);
		}
		while (j < BUFF_SIZE && buff[j] && buff[j] != '\n')
			j++;
		printf("j here =%d\n",j);
		if (buff[j] != '\n')
		{
			line_ct = line_ct + BUFF_SIZE;
			if (!(add = (char *)malloc(line_ct)))
				return (-1);
			printf("line_ct 444444 here=%d\n",line_ct);
			add = ft_strcpy (add, temp);
			add = ft_strncat(add, (const char *)buff, BUFF_SIZE);
			//free(temp);
			//free(buff);
			temp = add;
			//	free (add);
		}
		else
		{
			printf("j 6666666666 here =%d\n",j);
			*line = (char *)malloc(line_ct + j + 1);
			ft_bzero(*line, line_ct + j + 1);
			if (!*line)
				return (-1);
			printf("test here 7777777777777777777\n");
			if (temp)
			{
				line = ft_memmove (*line, temp, line_ct);
			}
			printf("test here 8888888888888888888888\n");
			*line = ft_strlcat(*line, (const char *)buff, line_ct + j + 1);
			printf("test here 99999999999999999999\n");
			ft_bzero(stock, BUFF_SIZE);
			temp = (char *)ft_memmove((void *)stock, (const void *)(buff + j + 1), BUFF_SIZE - j);
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
	fd = open(av[1], O_RDONLY);
	line = NULL;
	//write(1,"nihao\nhuhu\n\nsa\nlulu",20);
	get_next_line(fd ,line);
	ft_putendl(*line);
	return (0);
}

