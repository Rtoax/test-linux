#include "log.h"

#ifdef TEST_MAIN
int main(void)
{
	log_err("Hello\n");
	log_err("Hello %s\n", "World");

	log_parent("Parent. %d\n", 1);
	log_child("Child. %s\n", "Hello");

	return 0;
}
#endif
