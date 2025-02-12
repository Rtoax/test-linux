#!/bin/bash
set -ex

[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

# BPF_OBJ_NAME_LEN=16U, map name length need smaller than 15
# refs:
# - https://lore.kernel.org/lkml/tencent_26592A2BAF08A3A688A50600421559929708@qq.com/
map_name=$(mktemp -u tstmap______XXX)
map_type=array

sudo ${BPFTOOL} map create /sys/fs/bpf/${map_name} \
	type ${map_type} \
	key 4 value 4 entries 5 \
	name ${map_name}

sudo ${BPFTOOL} map show name ${map_name}
sudo ${BPFTOOL} map dump name ${map_name}

sudo ${BPFTOOL} map update name ${map_name} key 1 0 0 0 value 1 0 0 0
sudo ${BPFTOOL} map dump name ${map_name}

# Remove map from system
sudo unlink /sys/fs/bpf/${map_name}
