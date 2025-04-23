aarch64 Relocation
==================

# ELF64 aarch64

> ts=8

```
Name				Value	Calculation		Comment
-------------------------------------------------------------------------------
R_AARCH64_ABS64			257	S + A			No overflow check
R_AARCH64_ABS32			258	S + A
R_AARCH64_ABS16			259	S + A
R_AARCH64_PREL64		260	S + A - P		PC-relative 64-bits, No overflow check
R_AARCH64_PREL32		261	S + A - P		PC-relative 32-bits
R_AARCH64_PREL16		262	S + A - P		PC-relative 16-bits
R_AARCH64_MOVW_UABS_G0		263	S + A			Set a MOV[KZ] immediate field to bits [15:0] of X; check that 0 <= X < 2^16
R_AARCH64_MOVW_UABS_G0_NC	264	S + A			Set a MOV[KZ] immediate field to bits [15:0] of X. No overflow check
R_AARCH64_MOVW_UABS_G1		265	S + A			Set a MOV[KZ] immediate field to bits [31:16] of X; check that 0 <= X < 2^32
R_AARCH64_MOVW_UABS_G1_NC	266	S + A			Set a MOV[KZ] immediate field to bits [31:16] of X. No overflow check
R_AARCH64_MOVW_UABS_G2		267	S + A			Set a MOV[KZ] immediate field to bits [47:32] of X; check that 0 <= X < 2^48
R_AARCH64_MOVW_UABS_G2_NC	268	S + A			Set a MOV[KZ] immediate field to bits [47:32] of X. No overflow check
R_AARCH64_MOVW_UABS_G3		269	S + A			Set a MOV[KZ] immediate field to bits [63:48] of X (no overflow check needed)
R_AARCH64_MOVW_SABS_G0		270	S + A			Set a MOV[NZ] immediate field using bits [15:0] of X; check -2^16 <= X < 2^16
R_AARCH64_MOVW_SABS_G1		271	S + A			Set a MOV[NZ] immediate field using bits [31:16] of X; check -2^32 <= X < 2^32
R_AARCH64_MOVW_SABS_G2		272	S + A			Set a MOV[NZ] immediate field using bits [47:32] of X; check -2^48 <= X < 2^48
R_AARCH64_LD_PREL_LO19		273	S + A - P		Set a load-literal immediate value to bits [20:2] of X; check that -2^20 <= X < 2^20
R_AARCH64_ADR_PREL_LO21		274	S + A - P		Set an ADR immediate value to bits [20:0] of X; check that -2^20 <= X < 2^20
R_AARCH64_ADR_PREL_PG_HI21	275	Page(S+A)-Page(P)	Set an ADRP immediate value to bits [32:12] of the X; check that -2^32 <= X < 2^32
R_AARCH64_ADR_PREL_PG_HI21_NC	276	Page(S+A)-Page(P)	Set an ADRP immediate value to bits [32:12] of the X. No overflow check
R_AARCH64_ADD_ABS_LO12_NC	277	S + A			Set an ADD immediate value to bits [11:0] of X. No overflow check.
								Used with relocations ADR_PREL_PG_HI21 and ADR_PREL_PG_HI21_NC
R_AARCH64_LDST8_ABS_LO12_NC	278	S + A			Set an LD/ST immediate value to bits [11:0] of X. No overflow check.
								Used with relocations ADR_PREL_PG_HI21 and ADR_PREL_PG_HI21_NC
R_AARCH64_JUMP26		282	S + A - P		Set a B immediate field to bits [27:2] of X; check that -2^27 <= X < 2^27
R_AARCH64_CALL26		283	S + A - P		Set a CALL immediate field to bits [27:2] of X; check that -2^27 <= X < 2^27
R_AARCH64_LDST16_ABS_LO12_NC	284	S + A			Set an LD/ST immediate value to bits [11:1] of X. No overflow check
R_AARCH64_LDST32_ABS_LO12_NC	285	S + A			Set the LD/ST immediate value to bits [11:2] of X. No overflow check
R_AARCH64_LDST64_ABS_LO12_NC	286	S + A			Set the LD/ST immediate value to bits [11:3] of X. No overflow check
R_AARCH64_MOVW_PREL_G0		287	S + A - P		Set a MOV[NZ]immediate field to bits [15:0] of X
R_AARCH64_MOVW_PREL_G0_NC	288	S + A - P		Set a MOVK immediate field to bits [15:0] of X. No overflow check
R_AARCH64_MOVW_PREL_G1		289	S + A - P		Set a MOV[NZ]immediate field to bits [31:16] of X
R_AARCH64_LDST128_ABS_LO12_NC	299	S + A			Set the LD/ST immediate value to bits [11:4] of X. No overflow check
R_AARCH64_PLT32			314	S + A - P		Write bits [31:0] of X at byte-aligned place P. Check that -2^31 <= X < 2^31 see call and jump relocations.
```


# Links

- https://github.com/ARM-software/abi-aa/blob/main/aaelf64/aaelf64.rst
