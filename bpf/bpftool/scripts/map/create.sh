#!/bin/bash
set -ex

[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

# BPF_OBJ_NAME_LEN=16U, map name length need smaller than 15
# ref https://github.com/Rtoax/linux/commit/f4f16d527f7551d00ab9cb8bfe55b652f03b341a
map_name=$(mktemp -u tstmap______XXX)
map_type=array

sudo ${BPFTOOL} map create /sys/fs/bpf/${map_name} \
	type ${map_type} \
	key 4 value 4 entries 5 \
	name ${map_name}

sudo ${BPFTOOL} map show name ${map_name}
sudo ${BPFTOOL} map dump name ${map_name}

# Remove map from system
sudo unlink /sys/fs/bpf/${map_name}
