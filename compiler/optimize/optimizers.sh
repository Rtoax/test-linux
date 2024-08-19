#!/bin/bash

opts=(
	-O0
	-O1
	-O2
	-O3
	-Og
	-Os
	-Ofast
)

for o in ${opts[@]}
do
	gcc -Q --help=optimizers ${o} | tee optimizers${o}.log
done

info gcc 'Optimize Options' | tee info.log

