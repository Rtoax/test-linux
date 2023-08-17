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

# see: ls -l /dev/tty
# type = c = char
# major = 5, minor = 0 (tty)
# access = write
case $1 in
child-deny)
	echo "c 5:0 w" > /sys/fs/cgroup/devices/parent/child/devices.deny
	;;
child-allow)
	echo "c 5:0 w" > /sys/fs/cgroup/devices/parent/child/devices.allow
	;;
parent-deny)
	echo "c 5:0 w" > /sys/fs/cgroup/devices/parent/devices.deny
	;;
parent-allow)
	echo "c 5:0 w" > /sys/fs/cgroup/devices/parent/devices.allow
	;;
*)
	echo "
$0 [command]

parent-deny
parent-allow

child-deny
child-allow
	"
	;;
esac

