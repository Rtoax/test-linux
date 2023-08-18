#!/bin/bash
# link: https://0xax.gitbooks.io/linux-insides/content/Cgroups/linux-cgroups-1.html

set -e

if [[ ! -d /sys/fs/cgroup/devices ]]; then
	echo "ERROR: not support cgroup-v1"
	echo "MAYBE: sudo grubby --update-kernel=ALL --args=systemd.unified_cgroup_hierarchy=0"
	exit 1
fi

if [[ $(id -u | awk '{print $1}') != 0 ]]; then
	echo "ERROR: run with root(sudo)"
	exit 1
fi

# Create a cgroup and child cgroup
if [[ ! -d /sys/fs/cgroup/devices/parent ]]; then
	# Parent: parent
	# Child: child
	mkdir -p /sys/fs/cgroup/devices/parent/child
	ls /sys/fs/cgroup/devices/parent/
fi

# Add process to cgroup tasks
echo $(pidof -x cgroup_test_script.sh) > /sys/fs/cgroup/devices/parent/child/tasks

cgrp_file=
buffer="c 5:0 w"
# see: ls -l /dev/tty
# type = c = char
# major = 5, minor = 0 (tty)
# access = write
case $1 in
child-deny)
	shift
	cgrp_file=/sys/fs/cgroup/devices/parent/child/devices.deny
	;;
child-allow)
	shift
	cgrp_file=/sys/fs/cgroup/devices/parent/child/devices.allow
	;;
child-list)
	shift
	cat /sys/fs/cgroup/devices/parent/child/devices.list
	exit 0
	;;
parent-deny)
	shift
	cgrp_file=/sys/fs/cgroup/devices/parent/devices.deny
	;;
parent-allow)
	shift
	cgrp_file=/sys/fs/cgroup/devices/parent/devices.allow
	;;
parent-list)
	shift
	cat /sys/fs/cgroup/devices/parent/devices.list
	exit 0
	;;
*)
	echo "
$0 [command] [buffer]

[command]:
	parent-deny
	parent-allow
	parent-list

	child-deny
	child-allow
	child-list

[buffer] default: '${buffer}'
	type major:minor access
	+ type: a(all), c(char), b(block)
	+ access: w(write), r(read), m(mknod)
	"
	exit 1
	;;
esac

if [[ ! -z $1 ]]; then
	buffer=$1
fi

echo "${buffer}" > ${cgrp_file}
