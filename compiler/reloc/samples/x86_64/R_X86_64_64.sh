#!/bin/bash
set -e

. ../../../../elf/libelf.sh
. ../../../../libs/file.sh

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
	symsec=$(elf_sym2sec ${ELF_EXE} ${sym})
	symsecname=$(elf_sec2name ${ELF_EXE} ${symsec})
	symsecoffset=$(elf_sec2offset ${ELF_EXE} ${symsec})
	symsecaddr=$(elf_sec2addr ${ELF_EXE} ${symsec})
	symvalue=$(elf_sym2value ${ELF_EXE} ${sym})

	sym_file_off=$(( ${symvalue} - (${symsecaddr} - ${symsecoffset}) ))
	sym_file_val=$(read_hex_from_file ${ELF_EXE} ${sym_file_off} 8)

	printf "rela: %#lx %#lx %s ${sname} ${r_addend} ${r_secname}, " ${r_offset} ${r_info} ${r_type}
	printf "data: ${secdata} ${secdataname}, "
	printf "sym: %s sec %d %s %#lx val %#lx" ${sym} ${symsec} ${symsecname} ${symvalue} ${sym_file_val}
	printf "\n"
done <<< $(elf_foreachreloc_sec ${ELF_OBJ})
