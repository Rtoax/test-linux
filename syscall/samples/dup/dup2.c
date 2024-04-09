#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	FILE *fp = fopen("dup.txt", "w");
	fprintf(fp, "-------\n");
	dup2(fileno(fp), fileno(stdout));
	fprintf(stdout, "+++++++\n");
	fclose(fp);
	return 0;
}
