#!/bin/bash
pid=$(pidof pthread-gdb)
child_tid=$(ls /proc/$pid/task/ | tail -n1)

gdb -p $child_tid < pthread-gdb.gdb
