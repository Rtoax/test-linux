#include <fstab.h>
#include <stdio.h>

int main(void)
{
	setfsent();
	endfsent();
	return 0;
}
