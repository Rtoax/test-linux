/* Test data */
unsigned long bss_count = 0;
static unsigned long static_bss_count = 0;
unsigned long data_count = 1;
static unsigned long static_data_count = 1;
const unsigned long rodata_count = 1;
static const unsigned long static_rodata_count = 1;

static __attribute__((unused)) int static_func(void)
{
	return 0;
}
