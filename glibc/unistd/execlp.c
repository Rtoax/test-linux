#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main(void)
{
	int fd;

	fd = open("date.txt",O_RDWR | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	execlp("date", "date", NULL);

	return 0;
}
