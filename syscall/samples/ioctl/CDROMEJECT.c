#include <fcntl.h>
#include <linux/cdrom.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	ioctl(fd, CDROMEJECT);
	close(fd);
	return 0;
}
