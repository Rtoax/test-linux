#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

struct namelist {
	char name[64];
	struct namelist *next;
};

struct namelist rt1 = { "rt1", NULL };
struct namelist rt2 = { "rt2", NULL };
struct namelist rt3 = { "rt3", NULL };
struct namelist rt4 = { "rt4", NULL };

int main(int argc, char *argv[])
{
	rt1.next = &rt2;
	rt2.next = &rt3;
	rt3.next = &rt4;

	struct namelist *l1 = &rt1;

	while (l1) {
		printf("%s\n", l1->name);
		l1 = l1->next;
	}

	return 0;
}
