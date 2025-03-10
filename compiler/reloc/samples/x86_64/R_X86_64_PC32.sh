#!/bin/bash
set -e

. ../../../../elf/libelf.sh

ELF_OBJ=R_X86_64_PC32.o
ELF_EXE=R_X86_64_PC32

while read r_offset r_info r_type svalue sname r_addend r_secname
do
	# Skip unwind sections
	if [[ ${r_secname} =~ eh_frame ]]; then
		continue
	fi

	# Only handle R_X86_64_PC32
	if [[ ${r_type} != R_X86_64_PC32 ]]; then
		continue
	fi

	# FIXME: how to parse rela of .bss and .data
	# $ readelf --relocs --wide R_X86_64_PC32.o
	# Relocation section '.rela.text' at offset 0x478 contains 15 entries:
	#    Offset             Info             Type               Symbol's Value  Symbol's Name + Addend
	# 000000000000002b  0000000400000002 R_X86_64_PC32          0000000000000000 .bss + 10
	# 0000000000000041  0000000400000002 R_X86_64_PC32          0000000000000000 .bss + 18
	# 0000000000000063  0000000300000002 R_X86_64_PC32          0000000000000000 .data + 0
	# 000000000000006e  0000000300000002 R_X86_64_PC32          0000000000000000 .data + 8
	if [[ ${sname} == .bss ]] || [[ ${sname} == .data ]]; then
		continue
	fi

	sec=$(elf_name2sec ${ELF_OBJ} ${r_secname})
	sectext=$(elf_sec2info ${ELF_OBJ} ${sec})
	sectextname=$(elf_sec2name ${ELF_OBJ} ${sectext})
	sectextaddr=$(elf_sec2addr ${ELF_OBJ} ${sectext})
	sectextoff=$(elf_sec2offset ${ELF_OBJ} ${sectext})

	# Only text could get function with offset.
	if [[ ${sectextname} != .text ]]; then
		continue
	fi

	func=$(elf_off2func ${ELF_OBJ} $(( ${sectextaddr} + ${r_offset})) ${sectext} )
	funcaddr=$(elf_sym2value ${ELF_OBJ} ${func})

	exec_sectext=$(elf_name2sec ${ELF_EXE} ${sectextname})
	exec_sectextaddr=$(elf_sec2addr ${ELF_EXE} ${exec_sectext})
	exec_sectextoff=$(elf_sec2offset ${ELF_EXE} ${exec_sectext})

	exec_funcaddr=$(elf_sym2value ${ELF_EXE} ${func})
	exec_symaddr=$(elf_sym2value ${ELF_EXE} ${sname})
	rela_func_off=$(( ${r_offset} - (${funcaddr} - ${sectextaddr}) ))

	# R_X86_64_PC32: S + A - P
	pos=$(( ${exec_funcaddr} + ${rela_func_off} ))
	rela=$(( ${exec_symaddr} + ${r_addend} - ${pos} ))

	exec_rela_file_off=$(( ${exec_funcaddr} - (${exec_sectextaddr} - ${exec_sectextoff}) + ${rela_func_off} ))
	exec_rela_file_val=$(elf_hexfile ${ELF_EXE} ${exec_rela_file_off} 4)

	# FIXME: .bss and .data rela failed.

	printf ">>0x%lx 0x%016lx %s 0x%lx %s %s %s : " \
		${r_offset} ${r_info} ${r_type} ${svalue} ${sname} ${r_addend} ${r_secname}
	printf "sec %s %d %s addr:0x%lx sec:%d secoff 0x%lx, " \
		${r_secname} ${sec} ${sectextname} ${sectextaddr} ${sectext} ${sectextoff}
	printf "exe-sec addr:0x%lx off:0x%lx, " \
		${exec_sectextaddr} ${exec_sectextoff}
	printf "func %s obj:0x%lx exe:0x%lx, " \
		${func} ${funcaddr} ${exec_funcaddr}
	printf "rela: R_X86_64_PC32: S + A - P = 0x%lx + 0x%lx - 0x%lx = 0x%lx " \
		${exec_symaddr} ${r_addend} ${pos} ${rela}
	if [[ $(printf "%lx" ${rela}) == $(printf "%lx" ${exec_rela_file_val}) ]]; then
		printf " \033[1;32mSUCCESS "
	else
		printf " \033[1;31mERROR "
	fi
	printf "(0x%lx, fileoff:0x%lx, func:%s, funcoff:0x%lx)" \
		${exec_rela_file_val} ${exec_rela_file_off} ${func} ${rela_func_off}
	printf " \033[m\n"
done <<< $(elf_foreachreloc_sec ${ELF_OBJ})
