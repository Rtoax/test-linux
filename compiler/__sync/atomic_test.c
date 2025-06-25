/**
 * https://the-linux-channel.the-toffee-project.org/index.php?page=6-tutorials-linux-user-space-atomic-operations&lang=en
 * Author : Ramin Farajpour Cami
 */

#include <stdio.h>
#include "atomic.h"

int main(void)
{
	atomic_t v = ATOMIC_INIT(0);

	atomic_set(&v, 4);
	printf("%d\n", atomic_read(&v));

	atomic_add(2, &v);
	printf("%d\n", atomic_read(&v));

	atomic_inc(&v);
	printf("%d\n", atomic_read(&v));

	return 0;
}
