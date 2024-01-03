#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>		/*S_IRUSR */

int main(int argc, char *argv[])
{
	chown(argv[1], S_ISUID, S_ISGID);
	return 0;
}
