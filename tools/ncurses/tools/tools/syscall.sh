#!/bin/bash
set -e

sudo bpftrace -e \
'tracepoint:raw_syscalls:sys_enter {
	@enter += 1;
}
i:s:2 {
	printf("%ld\n", @enter);
	clear(@enter);
}
END {
	clear(@enter);
}
' 2>/dev/null | ../plotcake --title 'Syscalls' --ylabel 'N/s' \
			-l 'syscall'
