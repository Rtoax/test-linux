#!/bin/bash
set -x

make pthread-gdb
pid=$(pidof pthread-gdb)
if [[ -z "$pid" ]]; then
	./pthread-gdb &
	sleep 1
	pid=$(pidof pthread-gdb)
fi
tids=( $(ls /proc/$pid/task/) )
child_tid=${tids[1]}
parent_tid=${tids[0]}

gdb -p $child_tid -q < pthread-gdb.gdb
gdb -p $parent_tid -q < pthread-gdb.gdb

sleep 1
kill -9 ${pid}
