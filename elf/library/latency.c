#include <stdio.h>
#include <stdint.h>

#include "call.h"

int main(void)
{
	uint64_t i;
	uint64_t n = 1000000000UL;

	for (i = 0; i < n; i++) {
		call1();
		call2();
		call3();
		call4();
		call5();
		call6();
		call7();
		call8();
		call9();
		call10();
		call11();
		call12();
		call13();
		call14();
		call15();
		call16();
		call17();
		call18();
		call19();
		call20();
	}

	return 0;
}
