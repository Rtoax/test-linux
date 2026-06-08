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
	uint32_t name_len = info.name_len + 1;
	/**
	 * It's seems like no need to align 64:
	 *
	 * name_buf = mmap(NULL, info.name_len + 1, PROT_READ | PROT_WRITE,
	 *		   MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	 *
	 * posix_memalign((void **)&name_buf, 64, name_len);
	 */
	name_buf = malloc(name_len);
	memset(name_buf, 0, name_len);

	memset(&info, 0, sizeof(info));
	info.name = (uint64_t)name_buf;
	info.name_len = name_len;

	info_len = sizeof(info);

	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	if (err) {
		fprintf(stderr, "failed get info from fd %d at 2nd, %m.\n", fd);
		goto free_done;
	}

	printf("%s\n", name_buf);

free_done:
	free(name_buf);
done:
	if (fd > 0)
		close(fd);
	return err;
}
