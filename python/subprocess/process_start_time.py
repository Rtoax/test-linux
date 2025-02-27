#!/bin/env python

import subprocess
import re

def get_process_start_time(pid):
    try:
        command = f"ps -eo pid,lstart | grep {pid}"
        result = subprocess.check_output(command, shell=True).decode('utf-8')
        match = re.search(r'(\w+\s+\d+\s+\d+:\d+:\d+\s+\d+)', result)
        if match:
            return match.group(1)
        else:
            return "Start time not found"
    except subprocess.CalledProcessError:
        return "Process not found"

if __name__ == "__main__":
    pid = int(input("Enter the process ID (PID): "))
    start_time = get_process_start_time(pid)
    print(f"Process {pid} started at: {start_time}")
