#!/bin/bash

# $1 - ip address
# return 1-failed, 0-success
# echo FAIL-failed, OK-success
check_ipv4_address()
{
	local addr=$1
	local -a arr


	# '0.0.0.0.' is ill, only three '.' needed here.
	local nr_dot=$(echo $addr | tr -cd "." | wc -c)
	if [[ $nr_dot > 3 ]]; then
		echo "FAIL"
		return 1
	fi

	arr+=( $(echo $addr | awk -F '.' '{print $1}') )
	arr+=( $(echo $addr | awk -F '.' '{print $2}') )
	arr+=( $(echo $addr | awk -F '.' '{print $3}') )
	arr+=( $(echo $addr | awk -F '.' '{print $4}') )
	arr+=( $(echo $addr | awk -F '.' '{print $5}') )


	# 0.0.0.0.0 is not OK
	#         ^
	[[ ! -z ${arr[4]} ]] && echo "FAIL" && return 1

	for ((i = 0; i < 4; i++))
	do
		local a=${arr[$i]}
		# Empty
		if [[ -z $a ]]; then
			echo "FAIL"
			return 1
		# Number
		elif [[ -z "$(echo $a | grep -E '^[[:digit:]]*$')" ]]; then
			echo "FAIL"
			return 1
		# 0-255
		elif (( $a < 0 )) || (( $a > 255 )); then
			echo "FAIL"
			return 1
		fi
	done

	echo "OK"
	return 0
}

addresses=(
	# OK
	0.0.0.0
	127.0.0.1
	255.255.255.255
	# Not OK
	256.255.255.255
	ab.b.c.d
	-1.-1.-1.-1
	-1.0.0.2
	0
	0-
	-1
	0.0.-1.255
	0.0.-1.255
	0.0.1.-255
	0.0.1.255-
	0.0.1.255.12.1
	255.12.1..
	255.12.1.-.
	.
	.....
	....
	0.0.0.0.
	.0.0.0.0
	你.好.世.界
)

for a in ${addresses[@]}
do
	echo -n -e "$a: \t"
	if [[ $(check_ipv4_address $a) == OK ]]; then
		echo OK
	else
		echo FAIL
	fi
done

