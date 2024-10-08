#include <stdio.h>
#include <stdint.h>

#include "call.h"

int main(void)
{
	uint64_t i;
	uint64_t n = 1000000000UL;

	for (i = 0; i < n; i++) {
		call01();
		call02();
		call03();
		call04();
		call05();
		call06();
		call07();
		call08();
		call09();
		call010();
		call011();
		call012();
		call013();
		call014();
		call015();
		call016();
		call017();
		call018();
		call019();
		call020();
	}

	return 0;
}
