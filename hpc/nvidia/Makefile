subdir-y := cuda
subdir-y += nccl
subdir-y += ptx

target-y := driver-version

target-shell-y := driver-version.sh
target-shell-y += gpuinfo.sh

include main.mk

driver-version: driver-version.o
