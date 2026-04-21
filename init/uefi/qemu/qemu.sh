#!/bin/bash
set -ex

[[ ! -e boot.raw ]] && ln -s boot.img boot.raw

# Pass '-cdrom boot.img' if boot.img only is vfat
../../../scripts/qemu-vm.sh --disk boot.raw
