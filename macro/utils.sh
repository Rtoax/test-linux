#!/bin/bash

# $1 - ELF file
# $2 - function name
objdump_func()
{
	local bin=$1
	local func=$2

	echo -e "\033[1;32m>>> $bin:$func <<<\033[0m"

	gdb -batch \
		-ex "file $bin" \
		-ex "disassemble $func" \
		| sed 's/^/\t/g'
}

