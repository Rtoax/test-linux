#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>


void test0(void)
{
	FILE *fp;
	fp = fopen("/etc/os-release ", "r");
	if (fp || errno != ENOENT) {
		assert(!fp && "Forbidden space char in filename");
	}
}

void test1(void)
{
	FILE *fpw, *fpr;
	int i = 10;
	double fp = 1.5;
	char s[] = "this is a string";
	char c = '\n';
	char buff[123] = {0};

	fpr = fopen("/etc/os-release", "r");
	fpw = fopen("os-release", "w");

	while (fgets(buff, sizeof(buff), fpr)) {
		printf("%s", buff);
		fprintf(fpw, "%s", buff);
	}

	fprintf(fpw, "%s%c", s, c);
	fprintf(fpw, "%d\n", i);
	fprintf(fpw, "%f\n", fp);

	fclose(fpr);
	fclose(fpw);
}

int main(void)
{
	test0();
	test1();
	return 0;
}
