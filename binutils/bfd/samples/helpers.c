#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

void tl_bfd_print_build_id(const struct bfd_build_id *bid)
{
	int i;
	for (i = 0; i < bid->size; i++)
		printf("%02x", bid->data[i]);
	printf("\n");
}

