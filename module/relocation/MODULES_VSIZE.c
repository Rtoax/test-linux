#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/sizes.h>

/* .data */
#ifdef BIG_DATA
#pragma message("test bit data")
static char buff[SZ_128M] = {1};
#endif

#ifdef BIG_TEXT
#pragma message("test bit text")
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
MODULE_DESCRIPTION("Test MODULES_VSIZE");
