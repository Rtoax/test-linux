#include <stdio.h>
#include <stddef.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>


void with_other_locale(char *new_locale, void (*subroutine)(int), int argument)
{
	char *old_locale, *saved_locale;
	/* Get the name of the current locale. */
	old_locale = setlocale(LC_ALL, NULL);
	printf("old: %s\n", old_locale);

	/* Copy the name so it won’t be clobbered by setlocale. */
	saved_locale = strdup(old_locale);
	if (saved_locale == NULL)
		printf("Out of memory\n");

	/* Now change the locale and do some stuﬀ with it. */
	setlocale(LC_ALL, new_locale);
	(*subroutine)(argument);

	/* Restore the original locale. */
	setlocale(LC_ALL, saved_locale);

	free(saved_locale);
}

void do_something(int arg)
{
}

int main(void)
{
	with_other_locale("C", do_something, 0);
	return 0;
}
