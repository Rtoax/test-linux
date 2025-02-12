#!/bin/bash

./create.sh --name inner_arr1 --type array --no-unlink "$@"

./create.sh --name arr_maps --type array_of_maps --inner_map_name inner_arr1 --no-unlink "$@"

sudo rm -f /sys/fs/bpf/inner_arr1 /sys/fs/bpf/arr_maps
