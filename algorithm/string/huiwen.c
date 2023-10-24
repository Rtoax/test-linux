#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static struct test {
	char *str;
	bool test;
} tests_str[] = {
	{"abcdcba", true},
	{"abcddcba", true},
	{"aaaaaaa", true},
	{"aaaaaaaa", true},
	{"aaabbaaa", true},
	{"aaabaaa", true},
	{"abcdcbaabcdcbaabcdcba", true},
	{"abcddcbaabcddcbaabcddcba", true},
	{"aaaaaaaaaaaaaa", true},
	{"aaaaaaaaaaaaaaaa", true},
	{"aaabbaaaaaabbaaaaaabbaaa", true},
	{"aaabaaaaaabaaaaaabaaa", true},
};

bool check_huiwen(char *str)
{
	int i, len;
	if (!str)
		return false;

	len = strlen(str);
	if (len <= 0)
		return false;

	for (i = 0; i < len / 2; i++)
		if (str[i] != str[len-1-i])
			return false;

	return true;
}

int main(void)
{
	int i;

	for(i = 0; i < sizeof(tests_str) / sizeof(tests_str[0]); i++) {
		bool ret = check_huiwen(tests_str[i].str);

		printf("%-20s is %5s, %5s\n", tests_str[i].str, ret?"true":"false", ret==tests_str[i].test?"ok":"not ok");
	}
	return 0;
}
