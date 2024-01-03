#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <memory.h>

#define LEN		 8192
#define TEST_FILE   "text.out"

void gen_test_file(void)
{
	int i;
	char ch;
	FILE *fp = fopen(TEST_FILE, "w");

	ch = 'a';
	for (i = 0; i < 4096; i++)
		fwrite(&ch, 1, 1, fp);

	ch = 'b';
	for (i = 0; i < 4096; i++)
		fwrite(&ch, 1, 1, fp);

	fclose(fp);
}

void remove_test_file(void)
{
	unlink(TEST_FILE);
}

int main(void)
{
	int fd, ret;
	char str[LEN] = { 0 };
	char *start;

	gen_test_file();

	fd = open(TEST_FILE, O_RDWR);

	start = mmap(NULL, LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (start == MAP_FAILED) {
		perror("mmap");
		return -1;
	}

	memcpy(str, start, 8);
	printf("%s\n", str);

	memcpy(str, start + 4096, 8);
	printf("%s\n", str);

	memcpy(str, start + 4096 - 4, 8);
	printf("%s\n", str);

	/* 将文件的第二页重新映射到start位置 */
	ret = remap_file_pages(start, LEN >> 1, 0, 1, MAP_SHARED);
	if (ret < 0) {
		perror("remap_file_pages");
		munmap(start, LEN);
		close(fd);
		return 0;
	}

	/* 将文件的第一页重新映射到start+4096的位置。 */
	ret = remap_file_pages(start + 4096, LEN >> 1, 0, 0, MAP_SHARED);
	if (ret < 0) {
		perror("remap file pages failed2");
		munmap(start, LEN);
		close(fd);
		return 0;
	}

	memcpy(str, start, 8);
	printf("%s\n", str);

	memcpy(str, start + 4096, 8);
	printf("%s\n", str);

	memcpy(str, start + 4096 - 4, 8);
	printf("%s\n", str);

	munmap(start, LEN);
	close(fd);

	remove_test_file();

	return 0;
}
