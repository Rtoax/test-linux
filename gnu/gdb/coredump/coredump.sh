#!/bin/bash
# Usage: source this script: $ source coredump.sh
# Warning: do not use `set -x` here
#
# core_pattern:
# - |/usr/lib/systemd/systemd-coredump %P %u %g %s %t %c %h
#
bytes=unlimited

# run with it, generate a core.XXXX file.
function coredump() {
	echo "Core ${bytes} Bytes"
	ulimit -c ${bytes}
	echo 1 | sudo tee /proc/sys/kernel/core_uses_pid
	echo "./core.%e-%p-%t" | sudo tee /proc/sys/kernel/core_pattern
	echo 0 | sudo tee /proc/sys/kernel/nmi_watchdog
	echo 1 | sudo tee /sys/module/rcupdate/parameters/rcu_cpu_stall_suppress

	# or /etc/security/limits.conf add two lines:
	#   * soft core unlimited
	#   * hard core unlimited
	ulimit -c
	cat /proc/sys/kernel/core_pattern
}

if [ $# -gt 0 ]; then
	bytes=$1
	coredump
else
	echo "Usage: coredump.sh [bytes]"
	echo "set to ${bytes}"
	coredump
fi
