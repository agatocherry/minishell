#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int main(void)
{
	char *line;

	line = get_next_line(0);
	while (line != NULL)
	{
		write(1, line, strlen(line));
		free(line);
		line = get_next_line(0);
	}
	return (0);
}