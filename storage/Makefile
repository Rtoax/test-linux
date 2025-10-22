# SPDX-License-Identifier: GPL-3.0
subdir-y := scsi
subdir-y += lvm

target-shell-y := disk_examples.sh

target-y := partition-table

include ../template/main.mk

partition-table: partition-table.o
partition-table.o: mbr.h gpt.h
