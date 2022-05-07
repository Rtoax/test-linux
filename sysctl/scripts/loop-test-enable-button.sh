#!/bin/bash
# Test sysctl enable/disable flag
# Rong Tao
# 2022.04.26

# For example:
# kernel.ftrace_enabled
# fs.neg-dentry-enforce
ENABLED_NAME="fs.neg-dentry-enforce"

function test_loop_enable_disable()
{
	name=$1
	for ((i = 0;; i++))
	do
		value=$(expr $i % 2)
		iloop=$(expr $i % 100)
		test $iloop = 0 && echo "Test $i."
		sudo sysctl -w $name=$value >/dev/null
	done
}

# For example ENABLED_NAME=kernel.ftrace_enabled
test $# = 1 && ENABLED_NAME=$1

# ENABLED_NAME is not empty.
test ! -z $ENABLED_NAME && test_loop_enable_disable $ENABLED_NAME

