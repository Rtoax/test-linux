#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>


int main(int argc, char *argv[])
{
	int i, fd, idx;
	char event[64];
	struct input_event ev;


	/* My NUC10's keyboard is index 4 */
	idx = 4;

	for (i = 1; i < argc; i++)
		if (!strncmp(argv[i], "idx=", 4))
			idx = atoi(argv[i] + 4);

	fprintf(stderr, "Usage: %s [idx=IDX]\n", argv[0]);

	sprintf(event, "/dev/input/event%d", idx);

	if ((fd = open(event, O_RDONLY)) < 0) {
		perror("open(/dev/input/eventX)");
		exit(1);
	}

	fprintf(stderr, "Open %s read %ld bytes event\n", event, sizeof(ev));
	fprintf(stderr, "Press any keyboard to see what happen!!!\n");

	while (1) {
		read(fd, &ev, sizeof(ev));
		/* Keyboard event */
		if (ev.type == EV_KEY) {
			printf("Key %d (%s)\n", ev.code,
				ev.value ? "pressed" : "released");
		}
	}

	close(fd);

	return 0;
}
