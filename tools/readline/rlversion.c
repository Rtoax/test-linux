#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

#include <readline/readline.h>

int main(void)
{
	printf("%s\n", rl_library_version ? rl_library_version : "unknown");
	exit(0);
}
