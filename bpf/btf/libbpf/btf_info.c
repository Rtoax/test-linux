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
#include <sys/mman.h>
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

	printf("info1 len=%d, name=%llx, namelen=%d\n", info_len, info.name,
	       info.name_len);

	char *name_buf;
	posix_memalign((void **)&name_buf, 64, info.name_len + 1);
#if 0
	name_buf = mmap(NULL, info.name_len + 1, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#endif
	memset(name_buf, 0, info.name_len + 1);

	info.name = (uint64_t)name_buf;
	info.name_len = info.name_len + 1;

	info_len = sizeof(info);

	/**
	 * FIXME: 'Bad address' here
	 */
	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	if (err) {
		fprintf(stderr, "failed get info from fd %d at 2nd, %m.\n", fd);
		goto free_done;
	}

free_done:
	free(name_buf);
done:
	if (fd > 0)
		close(fd);
	return err;
}
