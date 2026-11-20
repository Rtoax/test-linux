#include <stdio.h>
#include <stdint.h>
#include <json-c/json.h>

int main(void)
{
	printf("%s\n", JSON_C_VERSION);
	printf("%d.%d.%d\n", JSON_C_MAJOR_VERSION, JSON_C_MINOR_VERSION,
	       JSON_C_MICRO_VERSION);
	return 0;
}
