#!/bin/bash
set -e

. libelf.sh

OBJ=R_X86_64_PC32.o
EXE=R_X86_64_PC32
SYM=gi32

r_off_add=( $(readelf --relocs --wide ${OBJ} \
		| grep -w R_X86_64_PC32 | grep -w ${SYM} \
		| awk '{print "0x"$1" "$(NF-1)$(NF)}') )
r_offset=${r_off_add[0]}
r_addend=${r_off_add[1]}
r_func=$(elf_off2func ${OBJ} ${r_offset})
printf "obj: %s : r_offset %s, r_addend %s, near func %s\n" ${SYM} ${r_offset} ${r_addend} ${r_func}

obj_text_sec=$(elf_name2sec ${OBJ} .text)
obj_text_sec_off=$(elf_sec2offset ${OBJ} ${obj_text_sec})
obj_text_sec_addr=$(elf_sec2addr ${OBJ} ${obj_text_sec})
exe_text_sec=$(elf_name2sec ${EXE} .text)
exe_text_sec_off=$(elf_sec2offset ${EXE} ${exe_text_sec})
exe_text_sec_addr=$(elf_sec2addr ${EXE} ${exe_text_sec})
printf "obj: .text: sec %d, addr 0x%lx, off 0x%lx\n" ${obj_text_sec} ${obj_text_sec_addr} ${obj_text_sec_off}
printf "exe: .text: sec %d, addr 0x%lx, off 0x%lx\n" ${exe_text_sec} ${exe_text_sec_addr} ${exe_text_sec_off}


obj_func_sec=$(elf_sym2sec ${OBJ} ${r_func})
obj_func_sh_addr=$(elf_sec2addr ${OBJ} ${obj_func_sec})
obj_func_sh_offset=$(elf_sec2offset ${OBJ} ${obj_func_sec})
obj_func_st_value=$(elf_sym2value ${OBJ} ${r_func})

exe_func_sec=$(elf_sym2sec ${EXE} ${r_func})
exe_func_sh_addr=$(elf_sec2addr ${EXE} ${exe_func_sec})
exe_func_sh_offset=$(elf_sec2offset ${EXE} ${exe_func_sec})
exe_func_st_value=$(elf_sym2value ${EXE} ${r_func})

obj_sym_st_value=$(elf_sym2value ${OBJ} ${SYM})
obj_sym_sec=$(elf_sym2sec ${OBJ} ${SYM})
obj_sym_sh_name=$(elf_sec2name ${OBJ} ${obj_sym_sec})
obj_sym_sh_addr=$(elf_sec2addr ${OBJ} ${obj_sym_sec})
obj_sym_sh_offset=$(elf_sec2offset ${OBJ} ${obj_sym_sec})

exe_sym_st_value=$(elf_sym2value ${EXE} ${SYM})
exe_sym_sec=$(elf_sym2sec ${EXE} ${SYM})
exe_sym_sh_name=$(elf_sec2name ${EXE} ${exe_sym_sec})
exe_sym_sh_addr=$(elf_sec2addr ${EXE} ${exe_sym_sec})
exe_sym_sh_offset=$(elf_sec2offset ${EXE} ${exe_sym_sec})

printf "obj: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s\n" \
	${r_func} ${obj_func_sec} ${obj_func_sh_addr} ${obj_func_sh_offset} ${obj_func_st_value}
printf "exe: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s\n" \
	${r_func} ${exe_func_sec} ${exe_func_sh_addr} ${exe_func_sh_offset} ${exe_func_st_value}

printf "obj: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${SYM} ${obj_sym_sec} ${obj_sym_sh_addr} ${obj_sym_sh_offset} ${obj_sym_st_value} ${obj_sym_sh_name}
printf "exe: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${SYM} ${exe_sym_sec} ${exe_sym_sh_addr} ${exe_sym_sh_offset} ${exe_sym_st_value} ${exe_sym_sh_name}

obj_func_sec_off=$(( ${obj_func_st_value} - (${obj_func_sh_addr} - ${obj_func_sh_offset}) ))
exe_func_sec_off=$(( ${exe_func_st_value} - (${exe_func_sh_addr} - ${exe_func_sh_offset}) ))

dd if=${OBJ} skip=$(printf %ld $(( ${obj_func_sec_off} + ${r_offset} ))) ibs=1 of=obj.bin count=4 2>/dev/null
dd if=${EXE} skip=$(printf %ld $(( ${exe_func_sec_off} + ${r_offset} ))) ibs=1 of=exe.bin count=4 2>/dev/null
hexdump -C obj.bin
hexdump -C exe.bin

pos=$(( ${exe_func_st_value} + ${r_offset} ))
val=$(( ${exe_sym_st_value} + ${r_addend} - ${pos} ))
printf "R_X86_64_PC32: %s : S + A - P = 0x%lx + %s - 0x%lx = 0x%lx\n" ${SYM} \
	${exe_sym_st_value} ${r_addend} ${pos} ${val}

