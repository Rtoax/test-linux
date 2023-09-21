#!/bin/bash

echo "console=ttyS0,115200 earlycon user_debug=31" > boot_emmc.cmd
mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "boot_emmc.cmd" -d boot_emmc.cmd boot_emmc.scr
