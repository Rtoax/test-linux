#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


struct vma {
	unsigned long start, end;
};

int main(void)
{
	int memfd, ret;
	FILE *mapsfp, *vdsofp;
	struct vma vma_vdso;
	void *mem;


	memfd = open("/proc/self/mem", O_RDONLY);
	if (memfd <= 0) {
		perror("open /proc/self/mem");
		return -1;
	}
	mapsfp = fopen("/proc/self/maps", "r");
	if (!mapsfp) {
		perror("fopen /proc/self/maps");
		return -1;
	}

	/* for each vma */
	fseek(mapsfp, 0, SEEK_SET);
	do {
		unsigned long start, end, offset;
		unsigned int major, minor, inode;
		char perms[5], name[256];
		char line[512];

		if (!fgets(line, sizeof(line), mapsfp))
			break;

		ret = sscanf(line, "%lx-%lx %s %lx %x:%x %d %255s",
			&start, &end, perms, &offset, &major, &minor,
			&inode, name);
		if (ret <= 0) {
			perror("sscanf");
			return -1;
		}

		if (!strcmp(name, "[vdso]")) {
			printf("Found vdso.\n");
			vma_vdso.start = start;
			vma_vdso.end = end;
			break;
		}
	} while (1);

	mem = malloc(vma_vdso.end - vma_vdso.start);
	if (!mem) {
		perror("malloc");
		return -1;
	}

	ret = pread(memfd, mem, vma_vdso.end - vma_vdso.start, vma_vdso.start);
	if (ret <= 0) {
		perror("pread");
		return -1;
	}
	vdsofp = fopen("vdso.so", "w");
	fwrite(mem, vma_vdso.end - vma_vdso.start, 1, vdsofp);

	close(memfd);
	fclose(mapsfp);
	fclose(vdsofp);
	return 0;
}
