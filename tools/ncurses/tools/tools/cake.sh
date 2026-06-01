#!/bin/bash
set -e

height=$(tput lines)
width=$(tput cols)

x10=$( printf "%0.s$((height / 3)) " $(seq 1 $((width / 5))) )
x20=$( printf "%0.s$((height / 2)) " $(seq 1 $((width / 3))) )
for i1 in 1 ${x10} ${x20} ${x10} 1 1
do
	echo $i1 ${height}
	sleep 0.01
done | ../plotcake --title 'Happy Birthday' -L unicode-heart -C RED -C white
