#!/bin/bash

sd=

[[ -e /dev/sda ]] && sd=/dev/sda
[[ -e /dev/vda ]] && sd=/dev/vda

[[ -z ${sd} ]] && echo "Not found sd" && exit 1

sudo dd if=${sd} of=mbr.bin bs=512 count=1

hexdump -C mbr.bin
