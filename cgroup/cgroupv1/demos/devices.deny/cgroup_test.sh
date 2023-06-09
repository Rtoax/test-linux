#!/bin/bash
# link: https://0xax.gitbooks.io/linux-insides/content/Cgroups/linux-cgroups-1.html

if [[ $(id -u | awk '{print $1}') != 0 ]]; then
	echo "ERROR: run with root(sudo)"
	exit 1
fi

mkdir /sys/fs/cgroup/devices/cgroup_test_group

ls /sys/fs/cgroup/devices/cgroup_test_group/

echo "c 5:0 w" > /sys/fs/cgroup/devices/cgroup_test_group/devices.deny

ls -l /dev/tty

echo $(pidof -x cgroup_test_script.sh) > /sys/fs/cgroup/devices/cgroup_test_group/tasks

