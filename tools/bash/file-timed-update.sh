#!/bin/bash

file_timed_update()
{
	local f1 f2 m1 m2
	f1=$1
	f2=$2
	m1=$(stat -c "%Y" $f1)
	m2=$(stat -c "%Y" $f2)

	# If modify time diff > 1s
	if [ $(($m2-$m1)) -gt 1 ]; then
		echo "You need to update $f1 to $f2"
	fi
}

touch a.out c.out
sleep 2
touch b.out

file_timed_update a.out b.out
file_timed_update a.out c.out
