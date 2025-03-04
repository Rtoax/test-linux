#!/bin/bash
set -e

OBJ=R_X86_64_PC32.o
EXE=R_X86_64_PC32
SYM=gi8
FUNC=foo

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

r_off_add=( $(readelf --relocs --wide ${OBJ} \
		| grep -w R_X86_64_PC32 | grep -w ${SYM} \
		| awk '{print "0x"$1" "$(NF-1)$(NF)}') )
r_offset=${r_off_add[0]}
r_addend=${r_off_add[1]}
printf "obj: %s : r_offset %s, r_addend %s\n" ${SYM} ${r_offset} ${r_addend}

obj_func_sec=$(sym2sec ${OBJ} ${FUNC})
obj_func_sh_name=$(sec2name ${OBJ} ${obj_func_sec})
obj_func_sh_addr=$(sec2addr ${OBJ} ${obj_func_sec})
obj_func_sh_offset=$(sec2offset ${OBJ} ${obj_func_sec})
obj_func_st_value=$(sym2value ${OBJ} ${FUNC})

exe_func_sec=$(sym2sec ${EXE} ${FUNC})
exe_func_sh_name=$(sec2name ${EXE} ${exe_func_sec})
exe_func_sh_addr=$(sec2addr ${EXE} ${exe_func_sec})
exe_func_sh_offset=$(sec2offset ${EXE} ${exe_func_sec})
exe_func_st_value=$(sym2value ${EXE} ${FUNC})

obj_sym_st_value=$(sym2value ${OBJ} ${SYM})
obj_sym_sec=$(sym2sec ${OBJ} ${SYM})
obj_sym_sh_name=$(sec2name ${OBJ} ${obj_sym_sec})
obj_sym_sh_addr=$(sec2addr ${OBJ} ${obj_sym_sec})
obj_sym_sh_offset=$(sec2offset ${OBJ} ${obj_sym_sec})

exe_sym_st_value=$(sym2value ${EXE} ${SYM})
exe_sym_sec=$(sym2sec ${EXE} ${SYM})
exe_sym_sh_name=$(sec2name ${EXE} ${exe_sym_sec})
exe_sym_sh_addr=$(sec2addr ${EXE} ${exe_sym_sec})
exe_sym_sh_offset=$(sec2offset ${EXE} ${exe_sym_sec})

printf "obj: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${FUNC} ${obj_func_sec} ${obj_func_sh_addr} ${obj_func_sh_offset} ${obj_func_st_value} ${obj_func_sh_name}
printf "exe: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${FUNC} ${exe_func_sec} ${exe_func_sh_addr} ${exe_func_sh_offset} ${exe_func_st_value} ${exe_func_sh_name}

printf "obj: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${SYM} ${obj_sym_sec} ${obj_sym_sh_addr} ${obj_sym_sh_offset} ${obj_sym_st_value} ${obj_sym_sh_name}
printf "exe: %s : section %-2d, sh_addr %s, sh_offset %s, st_value %s (%s)\n" \
	${SYM} ${exe_sym_sec} ${exe_sym_sh_addr} ${exe_sym_sh_offset} ${exe_sym_st_value} ${exe_sym_sh_name}

exe_func_sec_off=$(( ${exe_func_st_value} - (${exe_func_sh_addr} - ${exe_func_sh_offset}) ))

dd if=${OBJ} skip=$(printf %ld $(( ${obj_func_sh_offset} + ${r_offset} ))) ibs=1 of=obj.bin count=4 2>/dev/null
dd if=${EXE} skip=$(printf %ld $(( ${exe_func_sec_off} + ${r_offset} ))) ibs=1 of=exe.bin count=4 2>/dev/null
hexdump -C obj.bin
hexdump -C exe.bin

sym_offset=$( printf 0x%lx $(( ${exe_sym_st_value} - (${exe_sym_sh_addr} - ${exe_sym_sh_offset}) )) )
printf "exe: %s : sym_offset %s\n" ${SYM} ${sym_offset}

printf "%s : S + A - P = %s + %s + %s = %s\n" ${SYM} \
	${exe_sym_st_value} ${r_addend} ?? \
	??

