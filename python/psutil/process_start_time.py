#!/bin/env python
# Get process start time
import psutil
import time

def get_process_start_time(pid):
    try:
        process = psutil.Process(pid)
        return process.create_time()
    except psutil.NoSuchProcess:
        return -1

if __name__ == "__main__":
    pid = int(input("Enter the process ID (PID): "))
    start_time = get_process_start_time(pid)
    start_time_str = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(start_time))
    print("Process %d started at: %s" % (pid, start_time_str))
