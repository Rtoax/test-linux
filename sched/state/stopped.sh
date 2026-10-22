#!/bin/bash

_check_process_stopped() {
	local pid=$(pidof stopped)
	local status=$(cat /proc/$pid/wchan)

	if [ "$status" == "do_signal_stop" ] ; then
		echo "$pid do stopped: $status"
	else
		echo "$pid does not stopped: $status"
	fi

	if [[ "$(ps -o state= -p $pid)" = T ]]; then
		echo "$pid do stopped"
	else
		echo "$pid does not stopped"
	fi
}

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
	_check_process_stopped
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
