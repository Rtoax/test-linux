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

# TODO: it's not pid=1 somewhere
expect_ppid=1

# Get parent PID and check
pid=$(pgrep -n -f "${cmd}")
ppid=( $(ps -p ${pid} -o ppid | grep -v PPID) )

if [[ ${ppid} -ne ${expect_ppid} ]]; then
	echo 2>&1 "ERROR: cmd '${cmd}'(pid=${pid}) ppid is ${ppid}, should be ${expect_ppid}, something wrong!!"

	# Note: kill the child, otherwise will stuck 2s
	kill -9 ${pid}
	exit 1
else
	echo "Success!"
fi

kill -9 ${pid}
