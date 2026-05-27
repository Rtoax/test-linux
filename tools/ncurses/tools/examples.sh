#!/bin/bash
set -em

# loadavg will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

while sleep .2; do
	awk '{print $1, $2, $3}' /proc/loadavg
done | ./loadavg -t 2

echo "Byebye"
