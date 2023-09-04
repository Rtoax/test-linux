#!/bin/bash 

kvm=`grep -c -E '(vmx|svm)' /proc/cpuinfo`
if [ kvm = 0 ]; then
	echo "Not support vmx or svm"
else
	echo "Support KVM"
fi
