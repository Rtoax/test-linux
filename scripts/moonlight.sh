#!/bin/bash
set -e

readonly MOONLIGHT=( 🌑 🌒 🌓 🌔 🌕 🌖 🌗 🌘 🌑 )

sleep_sec()
{
	local secs=$(echo ${1} / 0.1 | bc)

	for ((i = 0; i < secs; i++))
	do
		printf "${MOONLIGHT[ $(($i % ${#MOONLIGHT[@]})) ]}"
		sleep 0.1
		printf "\b\b"
	done
}

if [[ $(basename $0) == moonlight.sh ]]; then
	sleep_sec 1
fi
