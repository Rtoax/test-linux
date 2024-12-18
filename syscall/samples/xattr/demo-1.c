#include <stdio.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int i, j, k;
	char list[1024] = {0};
	char value[1024] = {0};
	size_t size;
	char ch[100] = {0};
	char ch1[100] = {0}, ch2[100] = {0};
	char *file = "a.txt";

	strncpy(ch, file, 100);

	for (j = 0; j < 100; j++) {
		if ('\0' == ch[j])
		break;
		ch1[j] = ch[j];
	}

	printf("listxattr: %s\n", ch1);

	size = listxattr(ch1, list, 1024);
	printf("listxattr: %ld\n", size);

	for (i = 0; i < size; i++) {
		printf("%c", list[i]);

		if ('\0' == list[i]) {
			/**
			 * like $ getfattr [FILE]
			 */
			size = getxattr(ch1, ch2, value, 1024);
			printf("    %s %ld\n", value, size);
			memset(ch2, 0, 100);
			k = 0;
			continue;
		}
		ch2[k] = list[i];
		k++;
	}

	return 1;
}
