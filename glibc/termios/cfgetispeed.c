#include <stdio.h>
#include <termios.h>


int main(void)
{
	struct termios t;

	tcgetattr(fileno(stdout), &t);

	speed_t speedo = cfgetospeed(&t);

	printf("%d\n", speedo);

	speed_t speedi = cfgetispeed(&t);

	printf("%d\n", speedi);

	return 0;
}
