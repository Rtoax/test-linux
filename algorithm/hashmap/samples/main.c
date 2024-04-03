#include <stdio.h>
#include <string.h>
#include "hashmap.h"

static size_t str_hash_fn(const void *key, void *ctx)
{
	const char *s = key;
	size_t h = 0;

	while (*s) {
		h = h * 31 + *s;
		s++;
	}
	return h;
}

static bool str_equal_fn(const void *a, const void *b, void *ctx)
{
	return strcmp(a, b) == 0;
}

int main(void)
{
	size_t dup_cnt = 123;
	struct hashmap *type_names = hashmap__new(str_hash_fn, str_equal_fn, NULL);

	hashmap__set(type_names, "A", (void *)dup_cnt, NULL, NULL);

	size_t pdup_cnt = 0;
	hashmap__find(type_names, "A", (void **)&pdup_cnt);

	printf("pdup_cnt = %ld\n", pdup_cnt);

	hashmap__free(type_names);
	return 0;
}
