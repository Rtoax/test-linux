#!/bin/bash

./create.sh --name inner_hash1 --type hash --no-unlink "$@"
./create.sh --name inner_hash2 --type hash --no-unlink "$@"

./create.sh --name hash_maps --type hash_of_maps \
	--inner_map_name inner_hash1 --inner_map_name inner_hash2 \
	--no-unlink "$@"

sudo rm -f /sys/fs/bpf/inner_hash{1,2} /sys/fs/bpf/hash_maps
