/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkai <kkai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:28:48 by kkai              #+#    #+#             */
/*   Updated: 2021/05/11 01:26:45 by kkai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strchr(char *buff, char c)
{
	size_t	i;

	i = 0;
	while (buff[i] != '\0')
	{
		if (buff[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static int		ft_put_line(char **line, char **memo, char *buff)
{
	int		flag;
	size_t	n;
	char	*tmp;

	n_add = ft_strchar(buff, '\n');
	// 改行文字までをtmpに入れる tmp = aaa\n
	tmp = ft_strjoin(*line, buff, n_add);
	if (tmp == NULL)
		return (-1);
	free(*line);
	*line = tmp;
	tmp = NULL;
	flag = 0;
	if (buff[n_add] == '\n')
	{
		// 改行の先をtmpに入れる
		tmp = ft_strdup(buff[n_add + 1]);
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
	static char	*memo[256];
	char		*buff;
	int			flag;
	ssize_t		n;

	flag = 0;
	if (fd < 0 || 256 <= fd || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = (char *)malloc(sizeof(char) * 1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	flag = 0;
	if (memo[fd])
		flag = ft_put_line(line, &memo[fd], memo[fd]);
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
		return (-1);
	n = read(fd, buff, BUFFER_SIZE);
	while (flag == 0 && n > 0)
	{
		buff[n] = '\0';
		flag = ft_put_line(line, &memo[fd], buff);
		if (flag == 0)
			n = read(fd, buff, BUFFER_SIZE);
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
