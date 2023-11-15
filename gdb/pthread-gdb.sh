#!/bin/bash
set -x

make pthread-gdb
pid=$(pidof pthread-gdb)
if [[ -z "$pid" ]]; then
	./pthread-gdb &
	sleep 1
	pid=$(pidof pthread-gdb)
fi
child_tid=$(ls /proc/$pid/task/ | tail -n1)

gdb -p $child_tid < pthread-gdb.gdb

sleep 1
kill -9 ${pid}
