#!/bin/bash

. ../libs/qemu.sh

emulator=$(get_qemu_kvm_emulator)

${emulator} -M virt -cpu help
