#!/bin/bash
set -e

readonly MYDIR=$(dirname $(realpath $0))
. ${MYDIR}/lib-plotcake.sh

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
' 2>/dev/null | ${PLOTCAKE} --title 'Syscalls' --ylabel 'N/s' -l 'syscall' \
			-o syscall ${@}
