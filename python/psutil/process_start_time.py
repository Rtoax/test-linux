#!/bin/env python

import psutil
import time

pid = 1
process = psutil.Process(pid)

start_time = process.create_time()
start_time_str = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(start_time))

print("Process %d started at: %s" % (pid, start_time_str))
