#!/bin/bash
# Use binutils's readelf, objdump to parsing ELF file. binutils is different
# from elfutils, elfutils's eu-readelf, eu-objdump have totally different
# output format, it's not compatiable with each other.
set -e

readonly ELF_LIBC64=$(ldconfig -p | grep libc.so.6 | grep 64 | awk '{print $NF}')

__elf_sym_key2val() {
	local elf=$1
	local sym=$2
	local key=$3
	local value=$(readelf --syms --wide ${elf} \
		| awk -v sym=${sym} -v key=${key} '
		{
			if ($NF == sym) {
				if (key == "section") {
					print $(NF-1)
				}
				if (key == "st_value") {
					print "0x"$2
				}
			}
		}')
	if [[ -z ${value} ]]; then
		echo >&2 "ERROR: not found sym '${sym}' in ${elf}"
		exit 1
	else
		echo -n ${value}
	fi
}

elf_sym2sec() {
	__elf_sym_key2val $1 $2 section
}

elf_sym2value() {
	__elf_sym_key2val $1 $2 st_value
}

elf_name2sec() {
	local elf=$1
	local name=$2
	local value=$(readelf --sections --wide ${elf} | awk -v name=${name} '
		{
			# [ 1] .text
			if ($3==name) {
				print $2
			}
			# [1] .text
			if ($2==name) {
				print $1
			}
		}' | grep -o [0-9]*)

	if [[ -z ${value} ]]; then
		echo >&2 "ERROR: not found section '${name}' in ${elf}"
		exit 1
	else
		echo -n ${value}
	fi
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
	local elf off type secidx

	elf=$1
	shift
	off=$1
	shift

	while true; do
		if [[ "${1:0:5}" == "type=" ]]; then
			type=${1:5}
			shift
		elif [[ "${1:0:7}" == "secidx=" ]]; then
			secidx=${1:7}
			shift
		else
			break
		fi
	done
	# 14: 0000000000000020     8 OBJECT  GLOBAL DEFAULT    5 s9
	# 15: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    4 s10
	# 16: 0000000000000048     8 OBJECT  GLOBAL DEFAULT    2 pi1
	# 14: 0000000000000000    67 FUNC    GLOBAL DEFAULT    1 foo
	# 15: 0000000000000000    67 FUNC    GLOBAL DEFAULT    1 foo_alias2
	# 16: 0000000000000000    67 FUNC    GLOBAL DEFAULT    1 foo_alias1
	# 17: 0000000000000043    67 FUNC    GLOBAL DEFAULT    1 bar
	# 18: 0000000000000086    11 FUNC    GLOBAL DEFAULT    1 main
	readelf --syms --wide ${elf} | awk -v off=${off} -v type=${type} -v secidx=${secidx} '
		{
			if ($4 == type && $7 == secidx) {
				if (strtonum("0x"$2) <= strtonum(off) && strtonum("0x"$2) + strtonum($3) > strtonum(off)) {
					print $(NF)" +"(strtonum(off) - strtonum("0x"$2))
				}
			}
		}' | head -1
}

elf_off2func() {
	__off2sym_bias $1 $2 secidx=$3 type=FUNC | awk '{print $1}'
}

elf_off2object() {
	__off2sym_bias $1 $2 secidx=$3 type=OBJECT | awk '{print $1}'
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
		printf "0x%lx 0x%016lx %s 0x%lx %s %s%#lx %s\n" \
			0x${offset} 0x${info} ${type} 0x${svalue} ${sname} ${operator} 0x${addend} ${section}
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

elf_bss_syms() {
	local elf=$1
	local bss_secidx=$(elf_name2sec ${elf} .bss)
	local syms=( $(readelf --syms --wide ${elf} \
		| grep -w -e LOCAL -e GLOBAL \
		| awk -v secidx=${bss_secidx} '
		{
			if ($(NF-1) == secidx) {
				printf $NF" "
			}
		}')
		)
	echo ${syms[@]}
}

if [[ $# -ge 1 ]]; then
	ELF=/usr/bin/ls

	test_section_info() {
		names=( $(elf_rela_secnames ${ELF}) )
		for n in ${names[@]}; do
			sec=$(elf_name2sec ${ELF} ${n})
			sh_info=$(elf_sec2info ${ELF} ${sec})
			printf "%-16s : %-2d %-2d\n" ${n} ${sec} ${sh_info}
		done
	}
	test_section_info

	elf_foreachreloc ${ELF}
	elf_foreachreloc_sec ${ELF}
	elf_bss_syms ${ELF_LIBC64}
fi
