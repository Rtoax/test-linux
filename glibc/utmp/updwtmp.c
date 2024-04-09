#include <stdio.h>
#include <utmp.h>

int main(void)
{
	struct utmp *utmp = getutent();

	printf("ut_type: %d\n", utmp->ut_type);
	printf("ut_user: %s\n", utmp->ut_user);
	printf("ut_line: %s\n", utmp->ut_line);
	printf("ut_id: %s\n", utmp->ut_id);
	printf("ut_host: %s\n", utmp->ut_host);

	updwtmp("/home/rongtao/wtmp.out", utmp);

	return 0;
}
