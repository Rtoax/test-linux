#!/bin/bash
# osnoise tracing
#
# Copyright (C) 2023 Rong Tao.
#
# 2023-05-30	Rong Tao	Create this.
#

if [[ $(id -u) != 0 ]]; then
	echo "ERROR: running with root(sudo)"
	exit 1
fi

. /boot/config-$(uname -r)

if [[ $CONFIG_OSNOISE_TRACER != y ]]; then
	echo "ERROR: $(uname -r) is not support osnoise"
	exit 1
fi

current_tracer=$(cat /sys/kernel/tracing/current_tracer)
sec=2

echo "Tracing $sec seconds..."
echo osnoise > /sys/kernel/tracing/current_tracer

sleep $sec
cat /sys/kernel/tracing/trace

echo ${current_tracer} > /sys/kernel/tracing/current_tracer
