#!/bin/bash

pid_max=$(cat /proc/sys/kernel/pid_max)

echo -e "
Pid Max: ${pid_max}
"
