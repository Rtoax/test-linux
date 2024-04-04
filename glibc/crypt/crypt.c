#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <crypt.h>
#include <stdlib.h>
#include <string.h>


int main(void)
{
	int ok;
	const char *const pass = "12IbR.gJ8wcpc"; /* 123 */
	char *password;

	/* Turn it into printable characters from ‘seedchars’. */

	/* Read in the user’s password and encrypt it. */
	password = crypt(getpass("Password: "), "12");

	/* Print the results. */
	puts(password);

	ok = strcmp(password, pass);
	puts(!ok ? "Access granted." : "Access denied.");

	return 0;
}

