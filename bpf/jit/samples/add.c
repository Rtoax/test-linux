#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/mman.h>


long add(long num)
{
	return num + 4;
}

void emit_code_into_memory(unsigned char *m)
{
	/**
	 * long add4(long num) {
	 *     return num + 4;
	 * }
	 */
	unsigned char __attribute__((unused)) code1[] = {
		0x48, 0x89, 0xf8,       /* mov %rdi, %rax */
		0x48, 0x83, 0xc0, 0x04, /* add $4, %rax */
		0xc3,                   /* ret */
	};
	/* objdump -d add.o */
	unsigned char __attribute__((unused)) code2[] = {
		0x55,                   /* push   %rbp */
		0x48, 0x89, 0xe5,       /* mov    %rsp,%rbp */
		0x48, 0x89, 0x7d, 0xf8, /* mov    %rdi,-0x8(%rbp) */
		0x48, 0x8b, 0x45, 0xf8, /* mov    -0x8(%rbp),%rax */
		0x48, 0x83, 0xc0, 0x04, /* add    $0x4,%rax */
		0x5d,                   /* pop    %rbp */
		0xc3,                   /* retq */
	};

	memcpy(m, code2, sizeof(code2));
}

const size_t SIZE = 1024;
typedef long (*JittedFunc)(long);

void run_from_rwx(void)
{
	void *m = mmap(NULL, SIZE, PROT_READ | PROT_WRITE | PROT_EXEC,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	emit_code_into_memory(m);
	JittedFunc func = m;

	int result = func(2);

	printf("result = %d\n", result);
	munmap(m, SIZE);
}

int main(void)
{
	run_from_rwx();
	return 0;
}
