; ----------------------------------------------------------------------------
; maxofthree.asm
;
; NASM implementation of a function that returns the maximum value of its
; three integer parameters.  The function has prototype:
;
;   int maxofthree(int x, int y, int z)
;
; Note that only eax, ecx, and edx were used so no registers had to be saved
; and restored.
; ----------------------------------------------------------------------------

	global	maxofthree

	section .text
maxofthree:
	mov	eax, [esp+4]
	mov	ecx, [esp+8]
	mov	edx, [esp+12]
	cmp	eax, ecx
	cmovl	eax, ecx
	cmp	eax, edx
	cmovl	eax, edx
	ret
