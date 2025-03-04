#!/bin/bash
set -e

readonly RELOCS_X86_64=( $(grep -wo '^#define R_X86_64_[0-9A-Z_]*' /usr/include/elf.h | awk '{print $2}') )
readonly RELOCS_AARCH64=( $(grep -wo '^#define R_AARCH64_[0-9A-Z_]*' /usr/include/elf.h | awk '{print $2}') )
readonly RELOCS_386=( $(grep -wo '^#define R_386_[0-9A-Z_]*' /usr/include/elf.h | awk '{print $2}') )

readonly gen_file=relocs-gen.h

for r in ${RELOCS_X86_64[@]}
do
	printf "RELOC_X86_64(%s)\n" $r
done | tee ${gen_file}

for r in ${RELOCS_386[@]}
do
	printf "RELOC_I386(%s)\n" $r
done | tee --append ${gen_file}

for r in ${RELOCS_AARCH64[@]}
do
	printf "RELOC_AARCH64(%s)\n" $r
done | tee --append ${gen_file}
