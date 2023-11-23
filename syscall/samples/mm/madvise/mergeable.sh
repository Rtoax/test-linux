#!/bin/bash

make

dd if=/dev/zero of=ksm.dat bs=1M count=100

sudo sh -c 'echo 1 > /sys/kernel/mm/ksm/run'

./madvise-MADV_MERGEABLE ksm.dat &

printf "%-8s %-8s %-8s\n" SHARING SHARED UNSHARED
while :;
do
	sleep 1
	sharing=$(cat /sys/kernel/mm/ksm/pages_sharing)
	shared=$(cat /sys/kernel/mm/ksm/pages_shared)
	unshared=$(cat /sys/kernel/mm/ksm/pages_unshared)
	printf "%-8d %-8d %-8d\n" $sharing $shared $unshared
done
