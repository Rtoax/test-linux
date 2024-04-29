#!/bin/bash

for_each_args() {
	local i=0
	for p; do
		echo $i : $p
	done
}

for_each_args 1 2 3 a b c
