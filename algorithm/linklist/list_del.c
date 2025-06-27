#include <stdio.h>

typedef struct test {
	int val;
	struct test *next;
} *list;

int list_del(list l, int n)
{
	if(!l) return -1;

	while (l->next) {
		if (n == 1) {
			list *tmp = &l->next;

			*tmp = l->next->next;
		}
		l = l->next;
		n--;
	}
	return 0;
}

void for_each(list l)
{
	while (1) {
		if (l)
			printf("%d - ", l->val);
		else
			break;
		l = l->next;
	}
	printf("\n");
}

int main(void)
{
	struct test t0 = {0};
	struct test t1 = {1};
	struct test t2 = {2};
	struct test t3 = {3};
	struct test t4 = {4};

	t0.next = &t1;
	t1.next = &t2;
	t2.next = &t3;
	t3.next = &t4;
	t4.next = NULL;

	for_each(&t0);
	list_del(&t0, 1);
	for_each(&t0);

	return 0;
}
