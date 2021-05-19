/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkai <kkai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:28:48 by kkai              #+#    #+#             */
/*   Updated: 2021/05/20 04:53:27 by kkai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strchr(char *buff, char c)
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
	size_t	n_add;
	char	*tmp;

	n_add = ft_strchr(buff, '\n');
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
		// free(tmp);
		tmp = ft_strdup(&buff[n_add + 1]);
		if (tmp == NULL)
			return (-1);
		flag = 1;
	}
	free(*memo);
	*memo = tmp;
	// free(tmp);
	tmp = NULL;
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	static char	*memo[256];
	char		*buff;
	int			flag;
	ssize_t		n;

	if (fd < 0 || 256 <= fd || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	*line = (char *)malloc(1);
	if (*line == NULL)
		return (-1);
	*line[0] = '\0';
	flag = 0;
	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (buff == NULL)
	{
		free(*line);
		return (-1);
	}
	if (memo[fd])
		flag = ft_put_line(line, &memo[fd], memo[fd]);
	n = 0;
	if (flag == 0)
		n = read(fd, buff, BUFFER_SIZE);
	while (n > 0 && flag == 0)
	{
		buff[n] = '\0';
		flag = ft_put_line(line, &memo[fd], buff);
		if (flag == 0)
			n = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
	buff = NULL;
	if (flag == -1)
	{
		free(memo);
		*memo = NULL;
		free(*line);
	}
	if (n == -1)
		return (-1);
	return (flag);
}

// int    main(void)
// {
//     int    d = 1;
//     char    *line;
//     int    fd;
//     int    i = 1;

// 	fd = open("nl", O_RDONLY);
//     printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
//     while (d == 1)
//     {
//         printf("---%dline---\n", i);
//         d = get_next_line(fd, &line);//get_next_lineの第一引数がfdでないと、ファイルを読み込んだfdを指定できない。
//         printf("%s\t", line);
//         free(line);//ここがないと行数-1分リークする
//         printf("d : %d\n", d);
//         i++;
//     }
//     close(fd);
//     // put_mf();
//     system("leaks a.out");
//     return (0);
// }
