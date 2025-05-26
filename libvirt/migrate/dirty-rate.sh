#!/bin/bash
dom_name=cclinux2209

sudo virsh qemu-monitor-command ${dom_name} '{"execute":"calc-dirty-rate", "arguments": {"calc-time": 1}}' --pretty | jq
sudo virsh qemu-monitor-command ${dom_name} '{"execute":"query-dirty-rate"}' | jq
