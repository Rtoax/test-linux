#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "time_helpers.h"

#define TFILE "./tfile.txt"

int main(void)
{
	FILE *fp;
	struct tm *t;
	char *env;

	fp = fopen(TFILE, "w");
	fprintf(fp, "%%A\n");
	fprintf(fp, "%%T\n");
	fprintf(fp, "%%F\n");
	fclose(fp);

	setenv("DATEMSK", TFILE, 1);
	env = getenv("DATEMSK");
	printf("DATEMSK = %s\n", env);

	t = getdate("2009-12-28");
	if (t == NULL) {
		printf("getdate_err = %d\n", getdate_err);
	}

	print_tm(t);

	//unlink(TFILE);

	return 0;
}
