#!/bin/bash
# 
# Summarizing the tracepoint library names and numbers of tracepoints, on my
# Linux 4.10 system:
tp_list()
{
	sudo perf list | awk -F: '/Tracepoint event/ { lib[$1]++ } END {
		for (l in lib) { printf "  %-16.16s %d\n", l, lib[l] } }' | sort | column
}

# The following simple one-liner counts system calls for the executed command,
# and prints a summary (of non-zero counts):
tracepoint_date()
{
	sudo perf stat -e 'syscalls:sys_enter_*' date 2>&1 | awk '$1 != 0'
}

tracepoint_dd()
{
	sudo perf stat -e 'syscalls:sys_enter_*' dd if=/dev/zero of=/dev/null bs=512 count=1k | awk '$1 != 0'
}

strace_dd()
{
	sudo strace -c dd if=/dev/zero of=/dev/null bs=512 count=1k
}

case $1 in
list)
	tp_list 2>/dev/null
	;;
trace-date)
	tracepoint_date
	;;
trace-dd)
	tracepoint_dd
	;;
strace-dd)
	strace_dd
	;;
*)
	cat <<-EOF
	list         - show tracepoint list
	trace-date   - running 'date' tracepoint example
	trace-dd     - running 'dd' tracepoint example
	strace-dd    - running 'dd' strace example
	EOF
	;;
esac

