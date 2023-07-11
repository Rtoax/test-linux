#!/bin/bash

kmem_usage_in_bytes=( $(find /sys/fs/cgroup/ -name memory.kmem.usage_in_bytes) )

for u in ${kmem_usage_in_bytes[@]}
do
	echo -n "${u}: "
	cat $u
done
