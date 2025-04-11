/**
 * arm64 MODULES_VSIZE=SZ_128M or SZ_2G
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/sizes.h>

/* .data */
#ifdef BIG_DATA
#pragma message("test bit data")
static const char buff[SZ_128M] = {1};
#endif

#ifdef BIG_TEXT
#pragma message("test bit text")
const char __attribute__((section(".text"))) buff_in_text_section[SZ_128M] = {1};
#include "big-text.h"
#include "generated_functions.h"
#endif

static int kernel_init(void)
{
#ifdef BIG_TEXT
	call_big_text();
	call_big_text2();
#endif
	return -EINVAL;
}

module_init(kernel_init);
MODULE_AUTHOR("Rong Tao");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Test insmod big module");
