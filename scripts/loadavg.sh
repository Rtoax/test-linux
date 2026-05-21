#!/bin/bash
set -e

__loadavg=( $(cat /proc/loadavg) )
load1=${__loadavg[0]}
load5=${__loadavg[1]}
load15=${__loadavg[2]}
nproc=$(nproc)
echo ${load1} ${load5} ${load15}

# TODO: use ttyplot
