#!/bin/bash
set -e

ps -eo user,comm,pid,vsz,rss

comm_rss() {
	ps --no-headers -e -o comm,rss | awk '
		{
			name = $1;
			score = $2;
			total_score[name] += score;
			total_count[name] += 1;
		} END {
			for (name in total_score) {
				print total_score[name]"\t"total_count[name]"\t"name;
			}
		}' | sort -n
}

comm_rss_total() {
	comm_rss | awk '{ sum += $1 } END { print "Total RSS:\t"sum"kB" }'
}

comm_rss
comm_rss_total

