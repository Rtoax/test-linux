#!/bin/bash
# HMP: Human Monitor Protocol

# check the registers of VM
virsh qemu-monitor-command [vmname] --hmp --cmd info registers

# disassembler address ffffffffa74c3890
virsh qemu-monitor-command [vmname] --hmp --cmd x/16i 0xffffffffa74c3890

# show vm run status
virsh qemu-monitor-command [vmname] --hmp 'info status'
