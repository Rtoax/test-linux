#!/bin/bash
# Rong Tao <rongtao@cestc.cn>

# R - Running
# S - Sleeping
# D - Uninterruptible sleeping(Usually I/O)
# Z - Zombie
# T - Stop or Traced
# W - Memory Swap
# X - Dead
# < - Higher Priority
# N - Lower Priority
# L - Some page locked in memory
# s - Leader(has child tasks)
# l - Multi-thread, cloned-thread(CLONE_THREAD, NPTL pthreads)
# + - Background Tasks Group

find_state()
{
	ps -e -w -o stat,pid,lstart,comm | grep $1
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
test -z $1 && find_D
test ! -z $1 && find_state ^$1
