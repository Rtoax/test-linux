#!/bin/bash
# Rong Tao <rongtao@cestc.cn>

# man ps | grep -A 21 "^PROCESS STATE"
# R - Running
# S - Sleeping
# D - Uninterruptible sleeping(Usually I/O)
# Z - Zombie
# I - Idle kernel thread
# T - Stop or Traced
# W - Memory Swap
# X - Dead
# < - Higher Priority
# N - Lower Priority
# L - Some page locked in memory
# s - Leader(has child tasks)
# l - Multi-thread, cloned-thread(CLONE_THREAD, NPTL pthreads)
# + - Background Tasks Group

check_state()
{
	echo -e "\033[1;31musage: findD.sh [State]\033[m"
	echo    " [State] as follows:"
	man ps | grep -A 21 "^PROCESS STATE"
}

find_state()
{
	ps -e -w -o stat,pid,lstart,comm | grep $1 | nl
}

find_D()
{
	find_state ^D
}

find_Sleep()
{
	find_state ^S
}

# check D task by default
test -z $1 && check_state
test ! -z $1 && find_state ^$1

echo "Total tasks `ps -e | wc -l`"
