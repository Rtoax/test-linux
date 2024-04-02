	global  _start
	section .text
_start:
	vperm2i128  ymm0, ymm4, ymm6, 0x20
