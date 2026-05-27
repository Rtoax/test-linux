#!/bin/bash
# -m: (set -o monitor) monitor mode
set -em

tmout=2

# loadavg will send SIGINT to every processes in it's group, thus, we just
# catch SIGINT wo avoid this script execute failed.
sigint() {
	echo "SIGINT: $?"
	return 0
}
trap sigint INT

while sleep .2; do
	awk '{print $1, $2, $3}' /proc/loadavg
done | ./loadavg -t ${tmout}

while sleep .2; do
	free -m | grep ^Mem | awk '{print $2, $3, $4, $5, $6, $7}'
done | ./loadavg -t ${tmout}

echo "Byebye"
