#!/bin/bash
# see commit 9a48c9f46aa9 ("fork(2): ENOMEM: Test popen(2)")
# see commit 6aecb963d3fd ("syscall: namespace: test fork(2) return ENOMEM (todo)")
set -e

sudo ./unshare-execve -p -F -- ./dummy &

sleep 1

sudo ./setns -p $(pidof dummy) -n pid -- ./dummy-popen &

sleep 2

sudo kill -9 $(pidof dummy)

sleep 2

sudo kill -9 $(pidof dummy-popen)
