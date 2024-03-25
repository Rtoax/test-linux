#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"


void error_handling(const char* message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	exit(1);
}
