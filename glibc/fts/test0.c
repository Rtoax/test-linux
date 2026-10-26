#include <stdio.h>
#include <stdlib.h>
#include <fts.h>

int main(int argc, char *argv[])
{
	char *paths[] = { ".", NULL };

	FTS *ftsp = fts_open(paths, FTS_PHYSICAL | FTS_NOCHDIR, NULL);
	if (ftsp == NULL) {
		perror("fts_open");
		return EXIT_FAILURE;
	}

	FTSENT *node;

	while ((node = fts_read(ftsp)) != NULL) {
		switch (node->fts_info) {
		case FTS_D:
			printf("[DIR]  %s\n", node->fts_path);
			break;
		case FTS_F:
			printf("[FILE] %s\n", node->fts_path);
			break;
		case FTS_DP:
			break;
		default:
			printf("[OTHR] %s\n", node->fts_path);
			break;
		}
	}

	fts_close(ftsp);
	return EXIT_SUCCESS;
}
