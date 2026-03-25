#!/bin/bash
set -e

. ../scripts/libqemu.sh

emulator=$(get_qemu_kvm_emulator)

${emulator} -machine ?
