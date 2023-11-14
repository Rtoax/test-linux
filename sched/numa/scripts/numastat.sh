#!/bin/bash
# see: numastat -s

declare -a nodes_dir
declare -a numa_hit numa_miss numa_foreign
declare -a interleave_hit local_node other_node

for node in $(ls /sys/devices/system/node/)
do
	[[ $node != node[0-9]* ]] && continue
	dir=/sys/devices/system/node/$node
	nodes_dir+=( $dir )
	arr=( $( cat $dir/numastat | awk '{ print $2 }' ) )
	numa_hit+=( ${arr[0]} )
	numa_miss+=( ${arr[1]} )
	numa_foreign+=( ${arr[2]} )
	interleave_hit+=( ${arr[3]} )
	local_node+=( ${arr[4]} )
	other_node+=( ${arr[5]} )
done

echo "Total ${#nodes_dir[@]} NUMA"
printf "%-8s %-16s %-16s %-16s %-16s %-16s %-16s\n" \
	NODE NUMA_HIT NUMA_MISS FOREIGN INTER_HIT LOCAL OTHER
for ((i = 0; i < ${#nodes_dir[@]}; i++))
do
	printf "%-8s %-16s %-16s %-16s %-16s %-16s %-16s\n" \
		$(basename ${nodes_dir[$i]}) \
		${numa_hit[$i]} \
		${numa_miss[$i]} \
		${numa_foreign[$i]} \
		${interleave_hit[$i]} \
		${local_node[$i]} \
		${other_node[$i]}
done
