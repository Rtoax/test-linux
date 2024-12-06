#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *fpw, *fpr;
	int i = 10;
	double fp = 1.5;
	char s[] = "this is a string";
	char c = '\n';
	char buff[123] = {0};

	fpr = fopen("os-release", "r");
	fpw = fopen("os-release", "w");

	while (fgets(buff, sizeof(buff), fpr))
		printf("%s", buff);

	fprintf(fpw, "%s%c", s, c);
	fprintf(fpw, "%d\n", i);
	fprintf(fpw, "%f\n", fp);

	fclose(fpr);
	fclose(fpw);
	return 0;
}
