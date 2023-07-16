#include "log.h"

int main(void)
{
	log_err("Hello\n");
	log_err("Hello %s\n", "World");

	return 0;
}
