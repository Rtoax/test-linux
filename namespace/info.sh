#!/bin/bash
set -e

ps_ns_info()
{
	ps -e -o pidns,ipcns,mntns,netns,userns,utsns,cgroup,ppid,pid,cmd
}

process_detail()
{
	local lsns_ns_types=( mnt net ipc user pid uts cgroup time )
	local pgrep_ns_type=( ipc mnt net pid user uts )

	for lsns_type in ${lsns_ns_types[@]}
	do
		# sed: remove 1st line PID
		local ns_pids=( $(lsns -t ${lsns_type} -o pid | sed '1d') )
		for pid in ${ns_pids[@]}
		do
			for pgrep_type in ${pgrep_ns_type[@]}
			do
				echo -e "\033[1;31m## ${lsns_type}/${pid}/${pgrep_type}\033[m"
				# --ns: Match processes that belong to the same namespaces
				# --nslist: Match only the provided namespaces
				pgrep --ns ${pid} --nslist ${pgrep_type} -a
			done
		done
	done
}

case $1 in
ps)
	ps_ns_info
	;;
detail)
	process_detail
	;;
*)
	echo -e "Usage: $0 [ps|detail]"
	exit 1
	;;
esac

