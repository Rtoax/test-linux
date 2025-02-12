#!/bin/bash
set -ex

[[ -z ${BPFTOOL} ]] && BPFTOOL=bpftool

# BPF_OBJ_NAME_LEN=16U, map name length need smaller than 15
# refs:
# - https://lore.kernel.org/lkml/tencent_26592A2BAF08A3A688A50600421559929708@qq.com/
NAME=$(mktemp -u tstmap_XXXXXXXXXXXXXX)
NAME_truncate=${NAME:0:15}

TYPE=array

sudo ${BPFTOOL} map create /sys/fs/bpf/${NAME} \
	type ${TYPE} \
	name ${NAME_truncate} \
	key 4 value 4 entries 5

sudo ${BPFTOOL} map show name ${NAME_truncate}
sudo ${BPFTOOL} map dump name ${NAME_truncate}

sudo ${BPFTOOL} map update name ${NAME_truncate} key 1 0 0 0 value 1 0 0 0
sudo ${BPFTOOL} map dump name ${NAME_truncate}

# Remove map from system
sudo unlink /sys/fs/bpf/${NAME}
