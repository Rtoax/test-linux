#!/bin/bash
# Show clocksource devices
#
# 2023-04-20	Rong Tao	Create this.
#

prefix()
{
	echo -n -e "\033[32m$@\033[m"
}

prefix "available_clocksource: "
cat /sys/devices/system/clocksource/clocksource0/available_clocksource

prefix "current_clocksource: "
cat /sys/devices/system/clocksource/clocksource0/current_clocksource

