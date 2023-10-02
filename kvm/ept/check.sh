#!/bin/bash

ept=$(cat /sys/module/kvm_intel/parameters/ept)
vpid=$(cat /sys/module/kvm_intel/parameters/vpid)

echo "EPT:  $ept"
echo "VPID: $vpid"
