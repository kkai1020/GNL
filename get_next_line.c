/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkai <kkai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:28:48 by kkai              #+#    #+#             */
/*   Updated: 2021/05/09 00:37:02 by kkai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

int		ft_put_line(char **line, char **memo, char *buff)
{
	int		flag;
	size_t	n;
	char	*tmp;

	// 改行文字を探す
	n = ft_strchar(buff, '\n');
	// 改行文字までをtmpに入れる tmp = aaa\n
	tmp = ft_strjoin(*line, buff, -1, n);
	if (tmp == NULL)
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	flag = 0;
	if (buff[n] == '\n')
	{
		// 改行の先をtmpに入れる
		tmp = ft_strdup(buff + n + 1);
		if (tmp == NULL)
			return (-1);
		flag = 1;
	}
	free(*memo);
	*memo = tmp;
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	static char	*memo;
	int			flag;
	ssize_t		n;
	char		*buff;

	flag = 0;
	if (fd < 0 || MAX_FD <= fd || line == NULL)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = 0;
	if (memo)
		flag = ft_put_line(line, &memo, memo);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (-1);
	n = read(0, buff, BUFFER_SIZE);
	while (flag == 0 && n > 0)
	{
		buff[n] = 0;
		flag = ft_put_line(line, &memo, buff);
	}
	free(buff);
	if (flag == -1)
	{
		free(memo);
		memo = NULL;
		free(*line);
	}

	return (flag);
}
