#!/bin/bash

scaling_cur_freq=$(sudo cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq)

echo "Scaling Current Frequency ${scaling_cur_freq}"
