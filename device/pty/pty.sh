#!/bin/bash
set -e

for i in $(ls /dev/pts)
do
	echo "Hello from test-linux ${USER}@$(hostname), you are pty $i!" | sudo tee /dev/pts/$i
done
