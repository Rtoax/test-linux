#include <stdio.h>

void reverse_word(char *substr, int len)
{
	int i;
	for (i = 0; i < (len + 1) / 2; i++) {
		char ch = substr[i];
		substr[i] = substr[len-1-i];
		substr[len-1-i] = ch;
	}
}

void reverse_string_words(char *str)
{
	char *substr = str;

	while (*str != '\0') {
		while (*str == ' ') {
			str++;
			substr = str;
		}
		int sublen = 0;
		while (*str != ' ' && *str != '\0') {
			sublen++;
			str++;
		}
		reverse_word(substr, sublen);
	}
}

int main(void)
{
	char str1[] = {"<Hello World, My name is Rongtao, i'll talk to you later >"};

	printf("%s\n", str1);

	reverse_string_words(str1);

	printf("%s\n", str1);

	return 0;
}
