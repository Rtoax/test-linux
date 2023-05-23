#include <stdio.h>

#include "offsetof.h"
#include "align.h"

#define STRLEN	128

struct A {
	int id;
	int a;
	int offsetof;
};

struct test {
	int a;
	long b;
	int c;
};

struct father {
	int money;
	char firstname[STRLEN];
} __packed;

struct son {
	struct father father;
	char lastname[STRLEN];
} __packed;

int main()
{
	struct son son[] = {
		{
			.father.money = 10000,
			.father.firstname = {"Jone"},
			.lastname = {"lennon"},
		},
		{
			.father.money = 20000,
			.father.firstname = {"Jone"},
			.lastname = {"Tao"},
		},
	};

	printf("%ld\n", offsetof(struct A, a));
	printf("%ld\n", offsetof(struct A, offsetof));

	int pos = offsetof(struct test, c);
	printf("pos = %d\n", pos);

	printf("sizeof: %ld\n", sizeof(son));

	printf("offsetof: %ld\n", offsetof(typeof(struct son), father.firstname[3]));
	printf("offsetof: %ld\n", offsetof(struct son, father.firstname[2]));

	printf("I'm %s %s\n", son[1].father.firstname, son[1].lastname);
}

