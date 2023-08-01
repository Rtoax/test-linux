#!/bin/bash

set -e

interfaces=( $(ls /sys/class/net/) )
declare -a operstates carriers

# Get informations
for i in ${interfaces[@]}
do
	operstate=$(cat /sys/class/net/${i}/operstate 2>/dev/null || true)
	carrier=$(cat /sys/class/net/${i}/carrier 2>/dev/null || true)

	[[ -z $operstate ]] && operstate=Unknown
	[[ -z $carrier ]] && carrier=Unknown

	operstates+=( ${operstate} )
	carriers+=( ${carrier} )
done

# Print informations
printf "%-16s %-8s %-8s\n" INTERFACE STATE CARRIER
for ((i = 0; i < ${#interfaces[@]}; i++))
do
	printf "%-16s %-8s %-8s\n" \
		${interfaces[$i]} \
		${operstates[$i]} \
		${carriers[$i]}
done

