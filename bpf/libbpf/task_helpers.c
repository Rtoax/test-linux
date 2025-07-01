// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include "task_helpers.h"

const char *get_task_state(int state)
{
	/**
	 * Taken from:
	 * https://elixir.bootlin.com/linux/latest/source/include/linux/sched.h#L85
	 * There are a lot more states not covered here but these are common ones.
	 */
	switch (state) {
	case 0x0000: return "RUNNING";
	case 0x0001: return "INTERRUPTIBLE";
	case 0x0002: return "UNINTERRUPTIBLE";
	case 0x0200: return "WAKING";
	case 0x0400: return "NOLOAD";
	case 0x0402: return "IDLE";
	case 0x0800: return "NEW";
	default: return "<unknown>";
	}
}
