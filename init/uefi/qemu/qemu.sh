#!/bin/bash
set -ex

# Pass '-cdrom boot.img' if boot.img only is vfat
../../../scripts/qemu-vm.sh --disk boot.img --uefi novar
