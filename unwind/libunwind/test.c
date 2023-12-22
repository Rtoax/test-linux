#include <stdio.h>
#include <unistd.h>


void ddd(int n)
{
	if (n == 0)
		sleep(3000);
	else
		ddd(n - 1);
}

void ccc(void)
{
	ddd(10);
}

void bbb(void)
{
	ccc();
}

void aaa(void)
{
	bbb();
}

int main(void)
{
	aaa();
	return 0;
}
