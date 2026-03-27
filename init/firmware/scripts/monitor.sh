#!/bin/bash
set -e
# and start a new terminal, run: $ watch -n 0.1 'ls -l /sys/class/firmware/'
sudo udevadm monitor --environment --subsystem-match=firmware
