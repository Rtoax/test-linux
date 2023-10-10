#!/bin/bash

_check() {
	ps -e -w -o stat,pid,lstart,comm | grep stopped
}

_stop() {
	kill -19 $(pidof stopped)
}

_kill() {
	kill -9 $(pidof stopped)
}

_continue() {
	kill -18 $(pidof stopped)
}

case $1 in
check)
	_check
	;;
stop)
	_stop
	;;
kill)
	_kill
	;;
continue)
	_continue
	;;
*)
	echo "
$0 [check|stop|continue|kill]
"
	;;
esac
