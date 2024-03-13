#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	int i;
	double loadavg[3];
	getloadavg(loadavg, 3);

	for (i = 0; i < 3; i++) {
		printf("%lf\n", loadavg[i]);
	}
	return 0;
}
