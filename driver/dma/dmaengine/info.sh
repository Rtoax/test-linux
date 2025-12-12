#!/bin/bash
set -e

DMA=( $(ls /sys/class/dma/) )
IN_USE=( $(cat /sys/class/dma/dma*chan*/in_use) )
MEMCPY_COUNT=( $(cat /sys/class/dma/dma*chan*/memcpy_count) )
BYTES_XFER=( $(cat /sys/class/dma/dma*chan*/bytes_transferred) )


printf "%-10s %-4s %-10s %-16s\n" "DMA" "USE" "MEMCPY" "XFER(B)"
for ((i = 0; i < ${#DMA[@]}; i++))
do
	printf "%-10s %-4d %-10ld %-16ld\n" ${DMA[i]} ${IN_USE[i]} \
		${MEMCPY_COUNT[i]} ${BYTES_XFER[i]}
done
