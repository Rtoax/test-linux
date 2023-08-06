#!/bin/bash

sd=

[[ -e /dev/sda ]] && sd=/dev/sda
[[ -e /dev/vda ]] && sd=/dev/vda

sudo dd if=${sd} of=mbr.bin bs=512 count=1

hexdump -C mbr.bin
