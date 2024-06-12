#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE *stream;
	int i = 10;
	double fp = 1.5;
	char s[] = "this is a string";
	char c = '\n';

	stream = fopen("libcare-cc.log", "w");

	fprintf(stream, "%s%c", s, c);
	fprintf(stream, "%d\n", i);
	fprintf(stream, "%f\n", fp);

	fclose(stream);
	return 0;
}
