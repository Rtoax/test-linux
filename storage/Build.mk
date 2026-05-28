# SPDX-License-Identifier: GPL-3.0
include helpers.mk

subdir-y += io-sched
subdir-y += lvm
subdir-y += raid
subdir-y += scsi
subdir-y += nvme

target-y += partition-table
prog-y += disk_examples.sh

$(call target_link_helper,partition-table,TLC_HELPERS)
