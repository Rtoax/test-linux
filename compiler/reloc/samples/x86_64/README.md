x86_64 Relocation
=================


# Relocation Types

- `A`: Represents the addend used to compute the value of the relocatable field.
- `B`: Represents the base address at which a shared object has been loaded into memory during execution. Generally, a shared object is built with a 0 base virtual address, but the execution address will be different.
- `G`: Represents the offset into the global offset table at which the relocatio n entry’s symbol will reside during execution.
- `GOT`: Represents the address of the global offset table.
- `L`: Represents the place (section offset or address) of the Procedure Linkage Table entry for a symbol.
- `P`: Represents the place (section offset or address) of the storage unit being relocated (computed using `r_offset`).
- `S`: Represents the value of the symbol whose index resides in the relocation entry.
- `Z`: Represents the size of the symbol whose index resides in the relocation entry.

> The AMD64 ABI architectures uses only Elf64_Rela relocation entries with explicit addends. The r_addend member serves as the relocation addend.

```
Name				Value	Field		Calculation
-------------------------------------------------------------------------------
R_X86_64_NONE			0	none		none
R_X86_64_64			1	word64		S + A
R_X86_64_PC32			2	word32		S + A - P
R_X86_64_GOT32			3	word32		G + A
R_X86_64_PLT32			4	word32		L + A - P
R_X86_64_COPY			5	none		none
R_X86_64_GLOB_DAT		6	word64		S
R_X86_64_JUMP_SLOT		7	word64		S
R_X86_64_RELATIVE		8	word64		B + A
R_X86_64_GOTPCREL		9	word32		G + GOT + A - P
R_X86_64_32			10	word32		S + A
R_X86_64_32S			11	word32		S + A
R_X86_64_16			12	word16		S + A
R_X86_64_PC16			13	word16		S + A - P
R_X86_64_8			14	word8		S + A
R_X86_64_PC8			15	word8		S + A - P
R_X86_64_DTPMOD64		16	word64
R_X86_64_DTPOFF64		17	word64
R_X86_64_TPOFF64		18	word64
R_X86_64_TLSGD			19	word32
R_X86_64_TLSLD			20	word32
R_X86_64_DTPOFF32		21	word32
R_X86_64_GOTTPOFF		22	word32
R_X86_64_TPOFF32		23	word32
R_X86_64_PC64			24	word64		S + A - P
R_X86_64_GOTOFF64		25	word64		S + A - GOT
R_X86_64_GOTPC32		26	word32		GOT + A - P
R_X86_64_GOT64			27	word64		G + A
R_X86_64_GOTPCREL64		28	word64		G + GOT - P + A
R_X86_64_GOTPC64		29	word64		GOT - P + A
R_X86_64_GOTPLT64		30	word64		G + A
R_X86_64_PLTOFF64		31	word64		L - GOT + A
R_X86_64_SIZE32			32	word32		Z + A
R_X86_64_SIZE64			33	word64		Z + A
R_X86_64_GOTPC32_TLSDESC	34	word32
R_X86_64_TLSDESC_CALL		35	none
R_X86_64_TLSDESC		36	word64x2
R_X86_64_IRELATIVE		37	word64		indirect (B + A)
R_X86_64_RELATIVE64		38	word64		B + A
R_X86_64_GOTPCRELX		41	word32		G + GOT + A - P
R_X86_64_REX_GOTPCRELX		42	word32		G + GOT + A - P
```

- **ts=8**


# Links

- https://www.mindfruit.co.uk/posts/2012/06/relocations/#excerpts-from-the-amd-abi
- https://refspecs.linuxbase.org/elf/x86_64-abi-0.99.pdf
- https://refspecs.linuxbase.org/elf/x86_64-abi-0.98.pdf

