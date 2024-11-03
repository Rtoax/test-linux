#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <stdbool.h>
#include <libelf.h>
#include <sys/stat.h>

/**
 * ref https://sourceware.org/git/binutils-gdb.git
 * binutils/readelf.c:is_pie()
 */

int is_pie_raw(const char *path)
{
	int i, j, fd;
	void *mem = NULL;
	int res = false;
	struct stat statbuf;
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdrs;

	stat(path, &statbuf);

	fd = open(path, O_RDONLY);
	mem = malloc(statbuf.st_size);
	read(fd, mem, statbuf.st_size);
	close(fd);

	ehdr = mem;
	shdrs = mem + ehdr->e_shoff;

	for (i = 0; i < ehdr->e_shnum; i++) {
		Elf64_Shdr *shdr = &shdrs[i];

		if (shdr->sh_type != SHT_DYNAMIC)
			continue;

		fprintf(stderr, "%s found SHT_DYNAMIC.\n", path);
		Elf64_Dyn *dyns = mem + shdr->sh_offset;

		for (j = 0; j * shdr->sh_entsize < shdr->sh_size; j++) {
			Elf64_Dyn *dyn = &dyns[j];

			if (dyn->d_tag == DT_FLAGS_1) {
				if (dyn->d_un.d_val & DF_1_PIE) {
					fprintf(stderr, "%s is PIE\n", path);
					res = true;
					goto done;
				}
			}
		}
	}

	fprintf(stderr, "%s is not PIE\n", path);

done:
	free(mem);
	return res;
}

/**
 * See also https://github.com/iovisor/bcc/pull/5126
 */
int is_pie_libelf(const char *path)
{
	int res = false;
	int i, j, fd;
	Elf *elf;
	size_t shdrnum;

	fd = open(path, O_RDONLY);
	elf_version(EV_CURRENT);
	elf = elf_begin(fd, ELF_C_READ_MMAP, NULL);

	elf_getshdrnum(elf, &shdrnum);
	for (i = 0; i < shdrnum; i++) {
		Elf_Scn *scn = elf_getscn(elf, i);
		Elf64_Shdr *shdr = elf64_getshdr(scn);
		Elf_Data *data = elf_getdata(scn, NULL);

		if (shdr->sh_type != SHT_DYNAMIC)
			continue;

		fprintf(stderr, "%s found SHT_DYNAMIC.\n", path);
		Elf64_Dyn *dyns = data->d_buf;
		for (j = 0; j * shdr->sh_entsize < shdr->sh_size; j++) {
			Elf64_Dyn *dyn = &dyns[j];
			if (dyn->d_tag == DT_FLAGS_1) {
				if (dyn->d_un.d_val & DF_1_PIE) {
					fprintf(stderr, "%s is PIE\n", path);
					res = true;
					goto done;
				}
			}
		}
	}

	fprintf(stderr, "%s is not PIE\n", path);
done:
	elf_end(elf);
	close(fd);
	return res;
}

int main(int argc, char *argv[])
{
	char *path;

	fprintf(stderr, "Usage: %s [FILE=%s]\n", argv[0], argv[0]);

	path = (argc <= 1) ? argv[0] : argv[1];

	is_pie_raw(path);
	is_pie_libelf(path);

	return 0;
}
