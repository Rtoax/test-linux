#!/bin/bash 
# D - TASK_UNINTERRUPTIBLE
ps -e -w -o stat,pid,lstart,comm | grep ^D
