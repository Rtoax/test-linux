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

int next_btf(uint32_t *next_id)
{
	int fd = -1, err = 0;
	struct bpf_btf_info info = {};
	uint32_t id = *next_id, info_len = sizeof(info);
	char name_buf[128];

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

	info.name = (uint64_t)name_buf;
	info.name_len = sizeof(name_buf);

	err = bpf_obj_get_info_by_fd(fd, &info, &info_len);
	if (err) {
		fprintf(stderr, "failed get info from fd %d at 2nd, %m.\n", fd);
		goto done;
	}

#ifdef DEBUG
	printf("info len=%d, name=%llx, namelen=%d\n", info_len, info.name,
	       info.name_len);
#endif

	printf("%s (id %d)\n", name_buf, id);
done:
	if (fd > 0)
		close(fd);
	if (!err)
		*next_id = id;
	return err;
}

int main(int argc, char **argv)
{
	uint32_t id = 0;
	/**
	 * Get all kernel module BTF, looks like `lsmod`
	 */
	while (!next_btf(&id))
		;
	return 0;
}
