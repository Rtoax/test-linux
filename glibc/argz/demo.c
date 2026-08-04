#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argz.h>

int main(void)
{
	char *argz = NULL;
	size_t argz_len = 0;
	char *entry;

	/* Create an argz vector from a colon-separated string */
	if (argz_create_sep("one:two", ':', &argz, &argz_len) != 0) {
		perror("argz_create_sep");
		return 1;
	}

	printf("Initial argz (len=%zu):\n", argz_len);
	for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))
		printf(" - %s\n", entry);

	/* Add a new entry */
	if (argz_add(&argz, &argz_len, "three") != 0) {
		perror("argz_add");
		free(argz);
		return 1;
	}

	printf("\nAfter argz_add(\"three\") (len=%zu):\n", argz_len);
	for (entry = argz; entry; entry = argz_next(argz, argz_len, entry))
		printf(" - %s\n", entry);

	/* Find pointer to the entry "two" and delete it */
	char *to_delete = NULL;
	for (entry = argz; entry; entry = argz_next(argz, argz_len, entry)) {
		if (strcmp(entry, "two") == 0) {
			to_delete = entry;
			break;
		}
	}

	if (to_delete) {
		argz_delete(&argz, &argz_len, to_delete);
		printf("\nAfter argz_delete(\"two\") (len=%zu):\n", argz_len);
		for (entry = argz; entry;
		     entry = argz_next(argz, argz_len, entry))
			printf(" - %s\n", entry);
	} else {
		printf("\nEntry \"two\" not found to delete.\n");
	}

	free(argz);
	return 0;
}
