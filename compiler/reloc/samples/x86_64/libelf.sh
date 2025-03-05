#!/bin/bash
set -e

sym2sec() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print $(NF-1)}'
}

sym2value() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print "0x"$2}'
}

name2sec() {
	local elf=$1
	local name=$2
	readelf --sections --wide ${elf} | awk -v name=${name} '
		{
			# [ 1] .text
			if ($3==name) {
				print $2
			}
			# [1] .text
			if ($2==name) {
				print $1
			}
		}' | grep -o [0-9]*
}

sec2name() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print $(NF-9)}'
}

sec2offset() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-6)}'
}

sec2addr() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-7)}'
}

__off2sym_bias() {
	local elf=$1
	local off=$2
	local type=$3
	readelf --syms --wide ${elf} | awk -v off=${off} -v type=${type} '
		{
			if ($4 == type) {
				if (strtonum(0x$2) <= strtonum(off) && strtonum(0x$2) + $3 > strtonum(off)) {
					print $(NF)" +"(strtonum(off) - strtonum(0x$2))
				}
			}
		}' | head -1
}

off2func() {
	__off2sym_bias $1 $2 FUNC | awk '{print $1}'
}

foreachreloc() {
	local elf offset info type svalue sname operator addend

	elf=$1
	shift

	#     Offset             Info             Type      Symbol's Value  Symbol's Name + Addend
	# 0000000000000006  0000000800000002 R_X86_64_PC32  0000000000000000 gi8 - 5
	while read offset info type svalue sname operator addend
	do
		printf "0x%lx 0x%016lx %s 0x%lx %s %s%s\n" \
			0x${offset} 0x${info} ${type} 0x${svalue} ${sname} ${operator} ${addend}
	done <<< $(readelf --relocs --wide ${elf} | grep -e R_X86_64 -e R_AARCH64)
}

rela_secnames() {
	local elf=$1
	local relas=( $(readelf --sections --wide ${elf} \
			| awk '
			{
				# [ 2] .rela.text        RELA
				# or:
				#  [2] .rela.text        RELA
				if ($4 == "RELA" || $3 == "RELA") {
					print $(NF-9)
				}
			}'
			) )
	echo ${relas[@]}
}

if [[ $# -ge 1 ]]; then
	rela_secnames R_X86_64_PC32.o
	rela_secnames R_X86_64_PC32
fi
