#include <stdio.h>
#include <string.h>


void demo1(void)
{
	char source[] = "hello, world! welcome to china!";
	char delim[] = " ,!";

	char *s = strdup(source);
	char *token;

	for (token = strsep(&s, delim); token != NULL; token = strsep(&s, delim)) {
		printf("%s", token);
		printf("+");
	}
	printf("\n");
}

void demo2_man(void)
{
	char string[] = {"a/bbb///cc;xxx:yyy:"};
	char *stringp = strdup(string);
	const char *delim1 = ":;";
	const char *delim2 = "/";

	char *token, *subtoken;

	for (unsigned int j = 1; (token = strsep(&stringp, delim1)); j++) {
		printf("%u: %s\n", j, token);

		while ((subtoken = strsep(&token, delim2)))
			printf("\t --> %s\n", subtoken);
	}
}

int main(void)
{
	demo1();
	demo2_man();

	return 0;
}
