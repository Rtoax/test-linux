/**
 * links
 * - https://www.youtube.com/watch?v=RzrHuP2aVEg 56:38
 * - https://www.bilibili.com/video/BV1tu411v7XM/ 56:38
 */
#include <stdio.h>
#include <malloc.h>
#include <string.h>

/**
 * TODO: segvfault
 */
void emit_code_into_memory(unsigned char *m)
{
	/**
	 *	long add4(long num) {
	 *		return num + 4;
	 *	}
	 */
	unsigned char code[] = {
		0x48, 0x89, 0xf8,       /* mov %rdi, %rax */
		0x48, 0x83, 0xc0, 0x04, /* add $4, %rax */
		0xc3,                   /* ret */
	};

	memcpy(m, code, sizeof(code));
}

const size_t SIZE = 1024;
typedef long (*JittedFunc)(long);

void run_from_rwx(void)
{
	void *m = malloc(SIZE);
	emit_code_into_memory(m);
	JittedFunc func = m;
	int result = func(2);

	printf("result = %d\n", result);
	free(m);
}

int main(void)
{
	run_from_rwx();
}

