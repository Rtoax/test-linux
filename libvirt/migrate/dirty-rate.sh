#!/bin/bash
set -e

dom_name=almalinux9

sudo virsh qemu-monitor-command ${dom_name} '{"execute":"calc-dirty-rate", "arguments": {"calc-time": 1}}' --pretty | jq
sudo virsh qemu-monitor-command ${dom_name} '{"execute":"query-dirty-rate"}' | jq
