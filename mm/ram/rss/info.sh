#!/bin/bash
set -e

comm_rss() {
	ps --no-headers -eo comm,pid,rss | awk '
		{
			name = $1;
			rss = $3;
			total_rss[name] += rss;
			total_count[name] += 1;
		} END {
			for (name in total_rss) {
				print total_rss[name]"\t"total_count[name]"\t"name;
			}
		}' | sort -n
}

comm_rss_total_KB() {
	local kB=$(comm_rss | awk '{ sum += $1 } END { print sum }')
	echo ${kB}
}

comm_rss_total() {
	local kB=$(comm_rss_total_KB)
	printf "Total RSS:\t%ld KB, %ld MB, %ld GB\n" ${kB} $((${kB} / 1024)) \
		$((${kB} / 1024/ 1024))
}

# comm_rss
comm_rss_total

free -g
