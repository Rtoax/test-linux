#!/bin/bash
set -e

make uninterruptible

for ((i = 0; i < 100; i++))
do
	./uninterruptible vfork-sleep 10 &
done
