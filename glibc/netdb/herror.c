#include <stdio.h>
#include <netdb.h>

/**
 * 网络编程中的错误处理
 * void herror(char *s);
 * 这个函数会先输出这个“s”字符串，然后后面输出对应的错误信息。
 */

int main(void)
{
	char err[] = "err: this is a test ";
	herror(err);
	return 0;
}
