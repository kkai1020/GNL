#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifdef BUFFER_SIZE
#else
	#define BUFFER_SIZE (32)
#endif

int	get_next_line(int fd, char **line);

#endif
