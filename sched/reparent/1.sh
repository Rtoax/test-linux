#!/bin/bash
set -ex

echo pid=$$

cmd="sleep 3"

bash -c "${cmd} & exit"

pid=$(pgrep -n -f "${cmd}")
ppid=( $(ps -p ${pid} -o ppid | grep -v PPID) )

if [[ ${ppid} -ne 1 ]]; then
	echo 2>&1 "ERROR: cmd '${cmd}(pid=${pid})''s ppid(${ppid}) should be 1, something wrong!!"
	exit 1
fi

kill -9 ${pid}
