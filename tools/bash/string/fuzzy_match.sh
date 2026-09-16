#!/bin/bash
set -e

__fuzzy_match_diff_cnt() {
	local s="$1" t="$2"
	local n=${#s} m=${#t}
	local i j cost a b c min
	local prev curr

	if (( n > m + 5 || m > n + 5 )); then
		echo 999
		return
	fi

	prev=()
	for ((j=0; j<=m; j++)); do
		prev[j]=$j
	done

	for ((i=1; i<=n; i++)); do
		curr=()
		curr[0]=$i

		for ((j=1; j<=m; j++)); do
			if [ "${s:i-1:1}" = "${t:j-1:1}" ]; then
				cost=0
			else
				cost=1
			fi

			a=$(( prev[j] + 1 ))	# delete
			b=$(( curr[j-1] + 1 ))	# insert
			c=$(( prev[j-1] + cost ))	# replace

			min=$a
			(( b < min )) && min=$b
			(( c < min )) && min=$c

			curr[j]=$min
		done

		prev=("${curr[@]}")
	done

	echo "${prev[m]}"
}

fuzzy_match() {
	local dist
	dist=$(__fuzzy_match_diff_cnt "$1" "$2")
	[ "$dist" -le 5 ]
}

__fuzzy_match_diff_cnt "abc" "abc"
__fuzzy_match_diff_cnt "abc" "abc.c"
__fuzzy_match_diff_cnt "HygonGenuine_Hygon_C86-4G_OPN:7490.txt" "HygonGenuine-_Hygon_C86-4G-OPN_7490.txt"
__fuzzy_match_diff_cnt "123456" "12"
