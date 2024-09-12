#!/bin/bash

# Console tty
console_tty=$(cat /sys/class/tty/console/active)
echo "console=${console_tty}"
