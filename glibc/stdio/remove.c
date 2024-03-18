#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	mkdir("rong.out", 0777);
	remove("rong.out");

	return 0;
}

