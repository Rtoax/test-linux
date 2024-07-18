; FIXME: vfmadd231ps is FMA or AVX512ifma instruction
	global  _start
	section .text
_start:
	vfmadd231ps zmm1, zmm0, zmm17
