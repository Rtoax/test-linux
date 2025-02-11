#!/bin/bash
set -ex

map_name=map_tst1
map_type=array

sudo bpftool map create /sys/fs/bpf/${map_name} \
	type ${map_type} \
	key 4 value 4 entries 5 \
	name ${map_name}

sudo bpftool map show name ${map_name}
