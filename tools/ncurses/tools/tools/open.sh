#!/bin/bash
set -e

sudo bpftrace -e \
'tracepoint:syscalls:sys_enter_open* {
	@open += 1;
}
tracepoint:syscalls:sys_enter_close* {
	@close += 1;
}
i:s:1 {
	printf("%ld %ld\n", @open, @close);
	clear(@open);
	clear(@close);
}
END {
	clear(@open);
	clear(@close);
}
' 2>/dev/null | ../plotcake --title 'Open and Close Syscall Rate' --ylabel 'N/s' \
			-l 'open' -l 'close'
