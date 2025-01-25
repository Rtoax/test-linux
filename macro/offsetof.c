#include <stdio.h>

#include "offsetof.h"
#include "container_of.h"
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

struct mother {
	int age;
};

struct father {
	int age;
	int money;
	char firstname[STRLEN];
} __packed;

struct son {
	int age;
	struct mother mother;
	struct father father;
	char lastname[STRLEN];
} __packed;

#ifdef ERROR
union son {
	int a, b, c;
};
#endif

union person {
	struct mother mother;
	struct father father;
	struct son son;
};

int main(int argc, char *argv[])
{
	struct son *son;
	struct son sons[] = {
		{
			.age = 1,
			.mother.age = 23,
			.father.age = 23,
			.father.money = 10000,
			.father.firstname = {"Jone"},
			.lastname = {"lennon"},
		},
		{
			.age = 2,
			.mother.age = 32,
			.father.age = 32,
			.father.money = 20000,
			.father.firstname = {"Jone"},
			.lastname = {"Tao"},
		},
	};

	printf("%ld\n", offsetof(struct A, a));
	printf("%ld\n", offsetof(struct A, offsetof));

	int pos = offsetof(struct test, c);
	printf("pos = %d\n", pos);

	printf("size of son: %ld\n", sizeof(sons));

	printf("offsetof: %ld\n", offsetof(typeof(struct son), father.firstname[3]));
	printf("offsetof: %ld\n", offsetof(struct son, father.firstname[2]));

	printf("I'm %s %s\n", sons[1].father.firstname, sons[1].lastname);

	son = container_of(&sons[1].father, struct son, father);
	printf("son age: %d\n", son->age);

	printf("offsetof: %ld union\n", offsetof(union person, father.firstname));

	return 0;
}

