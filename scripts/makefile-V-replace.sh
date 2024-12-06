#!/bin/bash

Q() {
for m in $(find -name Makefile)
do
	line=$(sed -n '/SHELL =/=' $m)
	echo === $m, line $line
	sed "${line} a ifeq (\$(V),1)\n  Q =\nelse\n  Q = @\n  MAKEFLAGS += --no-print-directory\nendif\nexport Q\n" -i $m
done
}

Q2_NO_SHELL() {
for m in $(find -name Makefile)
do
	line=$(sed -n '/SHELL =/=' $m)
	[[ -z ${line} ]] && echo === $m no SHELL
done
}

CC() {
for m in $(find -name Makefile)
do
	echo === $m
	sed -i 's/@$(CC)/${Q}$(CC)/g' $m
	sed -i 's/@${CC}/${Q}$(CC)/g' $m
	sed -i 's/@$(CXX)/${Q}$(CXX)/g' $m
	sed -i 's/@${CXX}/${Q}$(CXX)/g' $m
	sed -i 's/@$(CLANG)/${Q}$(CLANG)/g' $m
	sed -i 's/@${CLANG}/${Q}$(CLANG)/g' $m
	sed -i 's/@rm/${Q}rm/g' $m
	sed -i 's/@${RM}/${Q}${RM}/g' $m
	sed -i 's/@make/${Q}make/g' $m
done
}
