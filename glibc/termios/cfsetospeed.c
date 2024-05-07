#include <stdio.h>
#include <termios.h>

int main(void)
{
	struct termios t;

	cfsetospeed(&t, 12);

	speed_t speedo = cfgetospeed(&t);

	printf("%d\n", speedo);

	cfsetispeed(&t, 11);

	speed_t speedi = cfgetispeed(&t);

	printf("%d\n", speedi);

	return 0;
}
