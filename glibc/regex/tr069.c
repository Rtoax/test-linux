#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Usage: %s string\n", argv[0]);
		return -1;
	}

	int status = 0, i = 0;
	int flag = REG_EXTENDED;
	regmatch_t pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;
	const char *pattern = "^Device\\.[a-zA-Z]\\w+\\.(([a-zA-Z0-9]\\w+|\\{[0-9]\\})\\.)*[a-zA-Z0-9]\\w+";
	char *buf = argv[1];

	regcomp(&reg, pattern, flag);
	status = regexec(&reg, buf, nmatch, pmatch, 0);
	if (status == REG_NOMATCH) {
		printf("\033[1;31mno match\033[m\n");
	} else if (status == 0) {
		printf("match success\n");
		for (i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++){
			putchar(buf[i]);
		}
		putchar('\n');
	}
	regfree(&reg);

	return 0;
}
