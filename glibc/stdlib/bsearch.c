/**
 * qsort()
 * bsearch()
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE(arr)  (sizeof((arr)) / sizeof((arr)[0]))

struct mi {
	int nr;
	const char *name;
};

static struct mi months[] = {
	{ 1, "jan" }, { 2, "feb" }, { 3, "mar" }, { 4, "apr" },
	{ 5, "may" }, { 6, "jun" }, { 7, "jul" }, { 8, "aug" },
	{ 9, "sep" }, {10, "oct" }, {11, "nov" }, {12, "dec" }
};

static int compmi(const void *m1, const void *m2)
{
	const struct mi *mi1 = m1;
	const struct mi *mi2 = m2;
	return strcmp(mi1->name, mi2->name);
}

int main(int argc, char *argv[])
{
	qsort(months, ARRAY_SIZE(months), sizeof(months[0]), compmi);
	for (size_t i = 1; i < argc; i++) {
		struct mi key;
		struct mi *res;

		key.name = argv[i];
		res = bsearch(&key, months, ARRAY_SIZE(months),
					  sizeof(months[0]), compmi);
		if (res == NULL)
			printf("'%s': unknown month\n", argv[i]);
		else
			printf("%s: month #%d\n", res->name, res->nr);
	}
	exit(EXIT_SUCCESS);
}
