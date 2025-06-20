# SPDX-License-Identifier: GPL-3.0
sub-dir := scsi
sub-dir += lvm

TARGETS := partition-table

include ../template/main.mk

partition-table: partition-table.o
partition-table.o: mbr.h gpt.h
