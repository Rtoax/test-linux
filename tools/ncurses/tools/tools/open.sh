#!/bin/bash
set -e

sudo bpftrace -e \
'tracepoint:syscalls:sys_enter_open* {
	@open += 1;
}
i:s:1 {
	printf("%ld\n", @open);
	clear(@open);
}' 2>/dev/null | \
../loadavg --title 'Open Syscall Rate' --ylabel 'N/s' -l 'open'
