#!/bin/bash
set -e

remote=cclinux2209
num_req=100

for ((i = 0; i < num_req; i++))
do
	ssh ${remote} uname -r &
done
