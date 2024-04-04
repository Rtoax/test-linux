#include <stdio.h>
#include <sys/xattr.h>

int main(int argc, char *argv[])
{
	char *file = "a.txt";

	int res = setxattr(file, "user.dog", "hachi", 2, 0); /*also tested 4 and 8*/
	printf("Result = %d\n", res);

	return 0;
}

