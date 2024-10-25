#!/bin/bash

container_pid_to_host_pid()
{
	local container_id=101c018f1995

	sudo podman container top ${container_id}
	sudo podman inspect -f '{{.State.Pid}}' ${container_id}
}

host_pid_to_container_pid()
{
	local host_pid=7830
	local pid_map=$(grep -i nspid /proc/${host_pid}/status)

	echo "${pid_map}"
}

lsns_container_namespace_id()
{
	# In container
	lsns
	#        NS TYPE   NPROCS PID USER COMMAND
	#4026531834 time        2   1 root bash
	#4026532854 user        2   1 root bash
	#4026532861 net         2   1 root bash
	#4026532926 mnt         2   1 root bash
	#4026532928 uts         2   1 root bash
	#4026532929 ipc         2   1 root bash
	#4026532930 pid         2   1 root bash
	#4026532931 cgroup      2   1 root bash
}

lsns_pid_namespace_pidlist()
{
	local nsid=4026532930
	ps -e -o pidns,pid | grep ${nsid}
}
