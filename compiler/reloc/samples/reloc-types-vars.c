
static int static_global_init_int = 1;
/* .bss */
static int static_global_uninit_int;
static int static_global_uninit_int2;

static int func(void)
{
	/**
	 * x86_64: R_X86_64_PC32
	 */
	static_global_init_int = 2;
	static_global_uninit_int = 3;
	static_global_uninit_int2 = 3;
	return 0;
}
