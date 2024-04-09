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

	setutent();
	struct utmp *ut = getutid(utmp);

	printf("ut_type: %d\n", ut->ut_type);
	printf("ut_user: %s\n", ut->ut_user);
	printf("ut_line: %s\n", ut->ut_line);
	printf("ut_id: %s\n", ut->ut_id);
	printf("ut_host: %s\n", ut->ut_host);
	endutent();


	return 0;
}
