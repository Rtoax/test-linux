/**
 * The out-of-band mark applies regardless of whether the receiving process is
 * receiving the out-of-band data inline (the SO_OOBINLINE socket option) or
 * out-of-band (the MSG_OOB flag). One common use of the out-of-band mark is
 * for the receiver to treat all the data as special until the mark is passed.
 */
#include <sys/socket.h>
#include <stdio.h>

int main(void)
{
	printf("SO_OOBINLINE = %d\n", SO_OOBINLINE);
	return 0;
}

