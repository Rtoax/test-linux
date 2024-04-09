#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <unistd.h>
#include <stdio.h>

int main(void)
{
#if 0 // TODO
	char key[64];	  /* bit pattern for key */
	char txt[64];	  /* bit pattern for messages */

	setkey(key);
	encrypt(txt, 0);	/* encode */
	encrypt(txt, 1);	/* decode */
#endif

	return 0;
}

