#!/bin/bash

for i in $(ls /dev/pts)
do
	echo Hello, you! > /dev/pts/$i
done
