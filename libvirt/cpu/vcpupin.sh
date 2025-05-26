#!/bin/bash

for i in $(seq 0 1 63)
do
	phy_cpu=$i
	diff_socket() {
		if [[ $i > 31 ]]; then
			phy_cpu=$(expr $i + 64)
		fi
	}
	diff_socket
	echo "<vcpupin vcpu='$i' cpuset='$phy_cpu'/>"
done
