#include <search.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct elem {
	struct elem *next, *prev;
	int v;
};

int main(void)
{
	struct elem *e;
	struct elem elems[] = {
		{ NULL, NULL, -1 },
		{ NULL, NULL, 1 },
		{ NULL, NULL, 2 },
	};

	insque(&elems[0], NULL);
	insque(&elems[1], &elems[0]);
	insque(&elems[2], &elems[1]);

	e = &elems[0];
	while (e) {
		printf("%d\n", e->v);
		e = e->next;
	}

	remque(&elems[1]);

	e = &elems[0];
	while (e) {
		printf("%d\n", e->v);
		e = e->next;
	}

	exit(EXIT_SUCCESS);
}
