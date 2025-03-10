#!/bin/bash
set -e

. ../../../../elf/libelf.sh

ELF_OBJ=R_X86_64_64.o
ELF_EXE=R_X86_64_64

while read r_offset r_info r_type svalue sname r_addend r_secname
do
	# Skip unwind sections
	if [[ ${r_secname} =~ eh_frame ]]; then
		continue
	fi

	sec=$(elf_name2sec ${ELF_OBJ} ${r_secname})
	secdata=$(elf_sec2info ${ELF_OBJ} ${sec})
	secdataname=$(elf_sec2name ${ELF_OBJ} ${secdata})

	sym=$(elf_off2object ${ELF_OBJ} ${r_offset} ${secdata})

	printf "%#lx %#lx %s ${sname} ${r_addend} ${r_secname}, " ${r_offset} ${r_info} ${r_type}
	printf "data: ${secdata} ${secdataname}, "
	printf "sym: %s" ${sym}
	printf "\n"
done <<< $(elf_foreachreloc_sec ${ELF_OBJ})
