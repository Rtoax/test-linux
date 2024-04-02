; avx2
; https://docs.oracle.com/cd/E36784_01/html/E36859/gntae.html
	global  _start
	section .text
_start:
	vperm2i128  ymm0, ymm4, ymm6, 0x20
