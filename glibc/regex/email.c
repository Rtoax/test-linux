#include <stdio.h>
#include <sys/types.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const char *emails[] = {
	"123456789@qq.com",	// success
	"rtoax@foxmail.com",	// success
	"###270401@163.com",	// failed
};

int main(void)
{
	int status = 0, ie, i;
	int flag = REG_EXTENDED;
	regmatch_t pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;
	const char *pattern = "^\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*$";

	regcomp(&reg, pattern, flag);

	for (ie = 0; ie < ARRAY_SIZE(emails); ie++) {
		const char *buf = emails[ie];
		status = regexec(&reg, buf, nmatch, pmatch, 0);
		if (status == REG_NOMATCH) {
			printf("'%s': no match\n", buf);
		} else if (status == 0) {
			printf("'%s': match success\n", buf);
			for (i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
				putchar(buf[i]);
			}
			putchar('\n');
		}
	}

	regfree(&reg);

	return 0;
}
