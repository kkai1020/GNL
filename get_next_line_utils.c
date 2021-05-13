/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkai <kkai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 16:24:15 by kkai              #+#    #+#             */
/*   Updated: 2021/05/13 17:33:25 by kkai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *line, char *buff, size_t n_add)
{
	char	*heap;
	size_t	i;
	size_t	j;

	if (line == NULL || buff == NULL)
		return (NULL);
	heap = (char *)malloc(ft_strlen(line) + ft_strlen(buff) + 1);
	if (heap == NULL)
		return (NULL);
	i = 0;
	while (line[i])
	{
		heap[i] = line[i];
		i++;
	}
	heap[i] = '\0';
	j = 0;
	while (j <= n_add)
		heap[i++] = buff[j++];
	heap[i] = '\0';
	return (heap);
}

char	*ft_strdup(char *src)
{
	char	*heap;
	size_t	i;

	i = ft_strlen(src);
	heap = (char *)malloc(sizeof(char) * (i + 1));
	if (heap == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		heap[i] = src[i];
		i++;
	}
	heap[i] = '\0';
	return (heap);
}
