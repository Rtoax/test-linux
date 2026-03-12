# SPDX-License-Identifier: GPL-3.0
subdir-y += io-sched
subdir-y += lvm
subdir-y += raid
subdir-y += scsi
subdir-y += nvme

target-y := partition-table
target-prog-y := disk_examples.sh
