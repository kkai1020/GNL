#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#ifdef BUFFER_SIZE
#else
	#define BUFFER_SIZE (32)
#endif

int		get_next_line(int fd, char **line);
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *line, char *buff, size_t n_add);
char	*ft_strdup(char *src);

#endif
