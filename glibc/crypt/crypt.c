#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <crypt.h>
#include <stdlib.h>


int main(void)
{
	char *password;

	/* Turn it into printable characters from ‘seedchars’. */

	/* Read in the user’s password and encrypt it. */
	password = crypt(getpass("Password: "), "12");

	/* Print the results. */
	puts(password);

	return 0;
}

