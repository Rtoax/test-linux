; avx512
; https://docs.oracle.com/cd/E37838_01/html/E61064/gsesq.html
	global  _start
	section .text
_start:
	KXORD k1, k3, k2
