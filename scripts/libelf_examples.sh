#!/bin/bash
set -e

. libelf.sh

readonly ELF=/usr/bin/ls
readonly ELF_LIBC64=$(ldconfig -p | grep libc.so.6 | grep 64 | awk '{print $NF}')

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
