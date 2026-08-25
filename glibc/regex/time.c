#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char *time_strs[] = {
	"10:10:10",	// success
	"10:10:10 ",	// failed
	"1:1:1",	// failed
	"10:10",	// failed
};

int main(void)
{
	const char *pattern = "^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9]$";

	regex_t regex;
	int reti, ie;

	reti = regcomp(&regex, pattern, REG_EXTENDED);
	if (reti) {
		fprintf(stderr, "regex compile failed\n");
		exit(EXIT_FAILURE);
	}

	for (ie = 0; ie < ARRAY_SIZE(time_strs); ie++) {
		const char *test_str = time_strs[ie];
		reti = regexec(&regex, test_str, 0, NULL, 0);
		if (!reti) {
			printf("'%s' match success\n", test_str);
		} else if (reti == REG_NOMATCH) {
			printf("'%s' match failed\n", test_str);
		} else {
			char msgbuf[100];
			regerror(reti, &regex, msgbuf, sizeof(msgbuf));
			fprintf(stderr, "regexec 错误: %s\n", msgbuf);
			regfree(&regex);
			exit(EXIT_FAILURE);
		}
	}

	regfree(&regex);
	return 0;
}
