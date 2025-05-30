#!/bin/bash
set -e
. ../../../qemu/libqemu.sh

qemu=$(get_qemu_kvm_emulator)

eval "sudo bpftrace -e 'uprobe:${qemu}:vhost* {@[probe] = count();}'"

