#!/bin/bash 

set -euo pipefail

function dmesg_tail() {
	sudo dmesg | tail -n 20
}
function dmesg_kernel_tail() {
	sudo dmesg -k | tail -n 20
}
dmesg_tail
