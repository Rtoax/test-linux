.data
.globl somedata
somedata:
	.8byte 0x42

.text
.globl _start
_start:
	nop
	ldr	x2, somedata
