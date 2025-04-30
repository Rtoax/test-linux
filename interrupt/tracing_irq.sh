#!/bin/bash
set -e

orig_val=$(sudo cat /sys/kernel/debug/tracing/events/irq/enable)

restore() {
	echo ${orig_val} | sudo tee /sys/kernel/debug/tracing/events/irq/enable
}
trap restore EXIT

echo 1 | sudo tee /sys/kernel/debug/tracing/events/irq/enable
sudo cat /sys/kernel/debug/tracing/trace_pipe
