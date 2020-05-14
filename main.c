#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main() {
	char *line;
	int fd;

	fd = open("/home/roman/CLionProjects/local_projects_scholl_21/school21_2c_get_next_line/txt", O_RDONLY);
	while (!get_next_line(fd, &line))
			printf("%s\n", line);
	return (0);
}
