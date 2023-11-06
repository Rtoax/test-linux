#include <unistd.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
	char *_argv[] = { "-a", NULL };
	execvp("ls", _argv);
	return 0;
}
