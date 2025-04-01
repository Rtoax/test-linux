#!/bin/bash
set -e

sudo mount -t tracefs

sudo cat /sys/kernel/tracing/README || {
	sudo cat /sys/kernel/debug/tracing/README
}
