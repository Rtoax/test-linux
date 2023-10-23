; ----------------------------------------------------------------------------
; factorial.asm
;
;    int factorial(int n) {
;        return (n <= 1) ? 1 : n * factorial(n-1);
;    }
; Illustration of a recursive function.
; ----------------------------------------------------------------------------	

	global factorial
	
	section .text
factorial:
        mov     eax, [esp+4]		; n
        cmp	eax, 1			; n <= 1
        jnle	L1			; if not, go do a recursive call
        mov	eax, 1			; otherwise return 1
        jmp	L2
L1:
	dec	eax			; n-1
	push	eax			; push argument
	call	factorial		; do the call, result goes in eax
	add	esp, 4			; get rid of argument
	imul	eax, [esp+4]		; n * factorial(n-1)
L2:
	ret
