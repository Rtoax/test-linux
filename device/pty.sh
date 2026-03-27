#!/bin/bash
set -e

for i in $(ls /dev/pts)
do
	echo "Hello, you $i!" | sudo tee /dev/pts/$i
done
