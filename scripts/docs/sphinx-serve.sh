#!/bin/bash
set -e

sphinx_build=$(dirname $(realpath $0))/sphinx-build.sh

file_monitor()
{
	local inotifywait_pid=
	while true
	do
		inotifywait --recursive \
			-e modify \
			-e delete \
			-e move \
			-e move_self \
			-e delete_self . &
		inotifywait_pid=$!

		wait $inotifywait_pid
		local exit_code=$?
		if [[ $exit_code -eq 0 ]]; then
			# build again
			$sphinx_build
		else
			break
		fi
	done
}

file_monitor &
monitor_pid=$!
pstree $monitor_pid

python -m http.server 8888 --directory ./build/html/ &
server_pid=$!

sig_handler()
{
	echo "Goodbye....... $monitor_pid, $server_pid"
	kill -9 $monitor_pid
	kill -9 $server_pid
}
trap sig_handler INT

wait $monitor_pid $server_pid
