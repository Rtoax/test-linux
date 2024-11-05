#include <glib.h>
#include <locale.h>

/* All of GThread is deprecated, but that’s OK */
G_GNUC_BEGIN_IGNORE_DEPRECATIONS

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	/* TODO */

	return g_test_run();
}

G_GNUC_END_IGNORE_DEPRECATIONS
