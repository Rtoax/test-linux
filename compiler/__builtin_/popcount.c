#include <stdio.h>

#define popcount(s) __builtin_popcount(s)

typedef struct {
	int pid;
	int sockfd;
} mac_t;

typedef struct {
	int id;
	int fd;
	int pid;
	mac_t mac;
} cell_t;

int main(void)
{
	cell_t cell = {
		.id = 1234,
		.fd = 21,
		.mac.pid = 121212,
	};

	/**
	 * TODO: expected ‘unsigned int’ but argument is of type ‘cell_t *’
	 */
	printf("%d\n", popcount(&cell));

	return 0;
}
