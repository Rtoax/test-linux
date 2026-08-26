#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Prints the environment, one environment variable to a line, of the process
 * given by PID.
 */
void print_process_environment(pid_t pid)
{
	int fd;
	char filename[24];
	char environment[8192];
	size_t length;
	char *next_var;

	/* Generate the name of the environ file for the process. */
	snprintf(filename, sizeof(filename), "/proc/%d/environ", (int)pid);

	/* Read the contents of the file. */
	fd = open(filename, O_RDONLY);
	length = read(fd, environment, sizeof(environment));
	close(fd);

	/* read does not NUL-terminate the buffer, so do it here. */
	environment[length] = '\0';
	/* Loop over variables. Variables are separated by NULs. */
	next_var = environment;

	while (next_var < environment + length) {
		/**
		 * Print the variable. Each is NUL-terminated, so just treat it
		 * like an ordinary string.
		 */
		printf("%s\n", next_var);
		/**
		 * Advance to the next variable. Since each variable is
		 * NUL-terminated, strlen counts the length of the next variable,
		 * not the entire variable list.
		 */
		next_var += strlen(next_var) + 1;
	}
}

int main(int argc, char *argv[])
{
	pid_t pid = getpid();

#define MY_ENV	"MY_NAME"

	setenv(MY_ENV, "Rong Tao", true);

	/* NOTE: setenv environment will not appear in /proc/self/environ */
	print_process_environment(pid);

	putenv(MY_ENV"=Koma");
	printf("%s: %s\n", MY_ENV, getenv(MY_ENV));

	return 0;
}
