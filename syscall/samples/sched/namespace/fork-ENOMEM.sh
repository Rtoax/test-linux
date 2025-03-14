#!/bin/bash
# see commit 9a48c9f46aa9 ("fork(2): ENOMEM: Test popen(2)")
# see commit 6aecb963d3fd ("syscall: namespace: test fork(2) return ENOMEM (todo)")
set -e

test1() {
	sudo ./unshare-execve -p -F -- ./dummy &
	sleep 1
	sudo ./setns -p $(pidof dummy) -n pid -- ./dummy-popen &
	sleep 2
	sudo kill -9 $(pidof dummy)
	sleep 2
	sudo kill -9 $(pidof dummy-popen)
}

test2() {
	# same as $ sudo unshare --pid ./dummy-fork
	# if add --fork argument to unshare, ENOMEM solved.
	sudo ./unshare-execve -p -- ./dummy-fork
}

test3() {
	sudo ./unshare-execve -p -- ./dummy-popen
}

case $1 in
test1 | test2 | test3)
	$1
	;;
*)
	echo >&2 "Usage: $0 [test1|test2|test3]"
	;;
esac

