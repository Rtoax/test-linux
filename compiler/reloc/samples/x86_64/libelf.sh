#!/bin/bash
set -e

elf_sym2sec() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print $(NF-1)}'
}

elf_sym2value() {
	local elf=$1
	local fun=$2
	readelf --syms --wide ${elf} | grep -w ${fun} | awk '{print "0x"$2}'
}

elf_name2sec() {
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

elf_sec2name() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print $(NF-9)}'
}

elf_sec2offset() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-6)}'
}

elf_sec2addr() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print "0x"$(NF-7)}'
}

# section sh_info: Additional section information
elf_sec2info() {
	local elf=$1
	local sec=$2
	readelf --sections --wide ${elf} | grep "\[[[:space:]]*${sec}\]" \
		| awk '{print $(NF-1)}'
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

elf_off2func() {
	__off2sym_bias $1 $2 FUNC | awk '{print $1}'
}

elf_foreachreloc() {
	local elf offset info type svalue sname operator addend

	elf=$1
	shift

	# Relocation section '.rela.text' at offset 0x400 contains 12 entries:
	#     Offset             Info             Type      Symbol's Value  Symbol's Name + Addend
	# 0000000000000006  0000000800000002 R_X86_64_PC32  0000000000000000 gi8 - 5
	while read offset info type svalue sname operator addend
	do
		printf "0x%lx 0x%016lx %s 0x%lx %s %s%s\n" \
			0x${offset} 0x${info} ${type} 0x${svalue} ${sname} ${operator} ${addend}
	done <<< $(readelf --relocs --wide ${elf} | grep -e R_X86_64 -e R_AARCH64)
}

elf_foreachreloc_sec() {
	local elf offset info type svalue sname operator addend section

	elf=$1
	shift

	while read offset info type svalue sname operator addend section
	do
		section=$(echo ${section} | tr -d "'")
		printf "0x%lx 0x%016lx %s 0x%lx %s %s%s %s\n" \
			0x${offset} 0x${info} ${type} 0x${svalue} ${sname} ${operator} ${addend} ${section}
	done <<< $(readelf --relocs --wide ${elf} | awk '
		BEGIN {
			section_name = "NULL"
		}
		{
			if ($1 == "Relocation") {
				section_name=$3
			}
			if (match($3, "R_X86_64_") || match($3, "R_AARCH64_")) {
				for (i=1; i<=NF; i++) {
					printf $(i)" "
				}
				printf section_name"\n"
			}
		}')
}

elf_rela_secnames() {
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
	test_section_info() {
		names=( $(elf_rela_secnames R_X86_64_PC32.o) )
		for n in ${names[@]}; do
			sec=$(elf_name2sec R_X86_64_PC32.o ${n})
			sh_info=$(elf_sec2info R_X86_64_PC32.o ${sec})
			printf "%-16s : %-2d %-2d\n" ${n} ${sec} ${sh_info}
		done
	}
	test_section_info

	elf_foreachreloc R_X86_64_PC32.o
	elf_foreachreloc_sec R_X86_64_PC32.o
fi
