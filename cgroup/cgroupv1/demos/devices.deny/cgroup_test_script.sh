#!/bin/bash

for i in $(seq 1 10000)
do
    echo "$i print line" > /dev/tty
    sleep 2
done
