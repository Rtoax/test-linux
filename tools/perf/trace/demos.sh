#!/bin/bash

# Trace the next 
#	two sched:sched_switch events, 
#	four block:*_plug events, 
#	the next block:*_unplug and 
#	the next three net:*dev_queue
# events, this last one with a backtrace of at most 16 entries, system wide:
sudo perf trace -e sched:*switch/nr=2/,block:*_plug/nr=4/,block:*_unplug/nr=1/,net:*dev_queue/nr=3,max-stack=16/

# strace
sudo perf trace cksum /usr/bin/cksum
