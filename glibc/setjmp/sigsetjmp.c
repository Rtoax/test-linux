#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

#define JMP_RET_VAL	10

#if defined(SIGJMP)
#define tl_jmp_buf	sigjmp_buf
#define tl_longjmp	siglongjmp
#define tl_setjmp(jmp)	sigsetjmp(jmp, 1)
#elif defined(JMP)
#define tl_jmp_buf	jmp_buf
#define tl_longjmp	longjmp
#define tl_setjmp(jmp)	setjmp(jmp)
#endif

tl_jmp_buf main_loop;

void abort_to_main_loop(int status)
{
	printf("%s:%d\n", __func__, status);
	tl_longjmp(main_loop, status);
}

void do_command(void)
{
	printf("%s: doing something...\n", __func__);
	abort_to_main_loop(JMP_RET_VAL);
}

int main(void)
{
	int ret;
	ret = tl_setjmp(main_loop);
	if (ret == JMP_RET_VAL) {
		printf("Back at main loop with val = %d\n", ret);
		return 0;
	}

	do_command();

	return 0;
}

