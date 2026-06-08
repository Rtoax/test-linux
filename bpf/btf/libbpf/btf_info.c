/**
 * btf info
 */
#include <bpf/libbpf.h>
#include <bpf/bpf.h>
#include <bpf/btf.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int fd = -1, err = 0;
	struct bpf_btf_info info = {};
	uint32_t id = 0, info_len = sizeof(info);

	err = bpf_btf_get_next_id(id, &id);
	if (err) {
		fprintf(stderr, "failed get next id.\n");
		exit(EXIT_FAILURE);
	}

	fd = bpf_btf_get_fd_by_id(id);
	if (fd < 0) {
		fprintf(stderr, "not support module btf.\n");
		exit(EXIT_FAILURE);
	}

	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	if (err) {
		fprintf(stderr, "failed get info from fd %d.\n", fd);
		goto done;
	}

	printf("info len=%d\n", info_len);

done:
	close(fd);
	return err;
}
