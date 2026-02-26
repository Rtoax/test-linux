#!/bin/bash
set -e

cmd="sleep 2"

if [[ $1 == setsid ]]; then
	setsid --fork ${cmd}
elif [[ $1 == bash ]]; then
	bash -c "${cmd} & exit"
else
	echo "Usage: $0 [setsid|bash]"
	exit 1
fi

# Get parent PID and check
pid=$(pgrep -n -f "${cmd}")
ppid=( $(ps -p ${pid} -o ppid | grep -v PPID) )

if [[ ${ppid} -ne 1 ]]; then
	echo 2>&1 "ERROR: cmd '${cmd}'(pid=${pid}) ppid is ${ppid}, should be 1, something wrong!!"

	# Note: kill the child, otherwise will stuck 2s
	kill -9 ${pid}
	exit 1
else
	echo "Success!"
fi

kill -9 ${pid}
