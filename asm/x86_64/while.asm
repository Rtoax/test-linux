        global  _start
        section .text
_start:
	push rbp
	mov rbp, rsp
while_1:
	nop
	jmp while_1
