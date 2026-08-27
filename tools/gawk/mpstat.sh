#!/bin/bash
set -e

mpstat -P ALL 1 | awk '
/^[0-9]{2}:[0-9]{2}:[0-9]{2}/ {
	idle[++n] = $NF
}
/^$/ {
	for (i = 1; i <= n; i++) {
		printf "%s%s", idle[i], (i == n ? "\n" : " ")
	}
	n = 0
}
'
