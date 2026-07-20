#!/bin/bash
# Work under Documentation directory
set -e

readonly MYDIR=$(dirname $(realpath $0))
readonly DOCDIR=$(realpath ${MYDIR}/../../Documentation/)
readonly sphinx_build=${MYDIR}/sphinx-build.sh

monitor_pid=
server_pid=
PORT=8888

hint()
{
	echo -e "\033[1;32m-----------------------------------------------\033[m"
	echo -e "\033[1;32mWebsite: http://localhost:${PORT}/\033[m"
	echo -e "\033[1;32m-----------------------------------------------\033[m"
}

kill_all()
{
	echo "Killing $monitor_pid, $server_pid"
	kill -9 $monitor_pid
	kill -9 $server_pid
}

file_monitor()
{
	local inotifywait_pid

	while true
	do
		inotifywait --recursive \
			-e modify \
			-e delete \
			-e move \
			-e move_self \
			-e delete_self . &
		inotifywait_pid=$!

		echo "Start a new inotifywait $inotifywait_pid"

		wait $inotifywait_pid
		local exit_code=$?
		if [[ $exit_code -eq 0 ]]; then
			# build again
			$sphinx_build || {
				continue
			}
			hint
		else
			kill_all
			break
		fi
	done
}

pushd ${DOCDIR}

file_monitor &
monitor_pid=$!
echo "Monitor $monitor_pid"

python -m http.server ${PORT} --directory ./build/html/ &
server_pid=$!
echo "Server $server_pid"
hint

sig_handler()
{
	kill_all
	popd
}
trap sig_handler INT EXIT

wait $monitor_pid $server_pid
