#!/bin/bash
set -e

release() {
	sudo umount $PWD/tmpfs || true
	rm -rf $PWD/tmpfs
}
trap release EXIT

mkdir -p $PWD/tmpfs

sudo mount tmpfs -t tmpfs -o size=1G -o mode=0777 $PWD/tmpfs


make flock

# Holding the flock for seconds
./flock -f $PWD/tmpfs/testfile -s 3 &

# Make sure flock above startup already
sleep 0.5

# Resource temporarily unavailable until above flock exit
while ! ./flock -f $PWD/tmpfs/testfile; do :; done

todo_while() {
	while true; do
		./flock -f $PWD/tmpfs/testfile || {
			ret=$?
			# EAGAIN (11) : Resource temporarily unavailable
			if [[ $ret == 11 ]]; then
				echo ">Resource temporarily unavailable<"
			fi
		}
	done
}
