#include <stdio.h>
#include <sys/types.h>

int http_get_response(char *buffer, int size, int rxed, char **msg_in)
{
	char *c;
	asprintf(&c, "%s%.*s", *msg_in, size * rxed, buffer);
	*msg_in = c;
	return size * rxed;
}

int main(void)
{
	char *msg = "rongtao";
	char buffer[1024] = "Hello. ";

	http_get_response(buffer, 10, 10, &msg);

	printf("%s\n", msg);
	return 0;
}
