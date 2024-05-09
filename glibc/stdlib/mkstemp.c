#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int write_temp_file(char *buffer, size_t length)
{
	char temp_filename[] = "tmp-XXXXXX";
	int fd = mkstemp(temp_filename);
	unlink(temp_filename);
	write(fd, &length, sizeof(length));
	write(fd, buffer, length);
	return fd;
}

char *read_temp_file(int fd, size_t *length)
{
	char *buffer;
	lseek(fd, 0, SEEK_SET);
	read(fd, length, sizeof(*length));
	buffer =(char *)malloc(*length);
	read(fd, buffer, *length);
	close(fd);
	return buffer;
}

int main(void)
{
	int fd;
	size_t length;
	char *buf;

	fd = write_temp_file("HELLO", 5);
	buf = read_temp_file(fd, &length);

	printf("%s\n", buf);
	free(buf);
	return 0;
}
