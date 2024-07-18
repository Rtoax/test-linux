; vperm2i128 is AVX2 instruction, not in AVX, this assembler use to check
; cpu feature contains AVX2 or not, if support trigger segvfault.
; Illegal instruction if not support.
; https://docs.oracle.com/cd/E36784_01/html/E36859/gntae.html
	global  _start
	section .text
_start:
	vperm2i128  ymm0, ymm4, ymm6, 0x20
