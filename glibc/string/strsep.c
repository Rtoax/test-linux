#include <stdio.h>
#include <string.h>


int demo1_errortry(void)
{
	char s1[] = {"rong tao is a good man"};
	char **s2 = NULL;
	strsep(s2, s1);
	printf("%s\n", s2[2]);
	return 0;
}

int main(void)
{
	char source[] = "hello, world! welcome to china!";
	char delim[] = " ,!";

	char *s = strdup(source);
	char *token;

	for (token = strsep(&s, delim); token != NULL; token = strsep(&s, delim)) {
		printf(token);
		printf("+");
	}
	printf("\n");
	return 0;
}
