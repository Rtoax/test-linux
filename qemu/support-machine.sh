#!/bin/bash
set -e

. libqemu.sh

emulator=$(get_qemu_kvm_emulator)

${emulator} -machine ?
