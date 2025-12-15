# SPDX-License-Identifier: GPL-3.0
subdir-y := scsi
subdir-y += io-sched
subdir-y += lvm
subdir-y += nvme

target-shell-y := disk_examples.sh

target-y := partition-table

include main.mk

partition-table: partition-table.o
partition-table.o: mbr.h gpt.h
