#include <stdio.h>
#include "ksym_helpers.h"

int main(void)
{
	load_kallsyms();
	return 0;
}
