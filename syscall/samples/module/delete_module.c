#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "mod_helpers.h"

int main(int argc, char *argv[])
{
	sys_delete_module("mymod", O_NONBLOCK);
	return 0;
}

