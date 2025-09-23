#!/bin/bash
set -e

remote=nucc11
num_req=100

for ((i = 0; i < num_req; i++))
do
	ssh ${remote} uname -r &
done
