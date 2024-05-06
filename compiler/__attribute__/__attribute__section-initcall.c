#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define debug() do { \
		printf("%s:%d %s\n", __FILE__, __LINE__, __func__); \
	} while (0)

typedef void (*init_call)(void);

#define _init __attribute__((unused, section(".myinit")))

#define DECLARE_INIT(func) init_call _fn_##func _init = func

static void A_init(void)
{
	debug();
}
DECLARE_INIT(A_init);

static void B_init(void)
{
	debug();
}
DECLARE_INIT(B_init);

static void C_init(void)
{
	debug();
}
DECLARE_INIT(C_init);

void do_initcalls(void)
{
	init_call init = A_init;
	for (; init < C_init; init++) {
		printf("init address: %p\n", init);
		init();
	}
}

int main(void)
{
	do_initcalls();
	return 0;
}
