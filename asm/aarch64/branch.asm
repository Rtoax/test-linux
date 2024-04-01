/**
 * https://www.cnblogs.com/dream397/p/15523421.html
 *
 * as branch.S -o branch.o
 * ld -o branch branch.o -lc -I /lib64/ld-linux-aarch64.so.1
 */
.data
	msg_start: .asciz "proc start \n"
	msg_end: .asciz "proc end \n"
	msg_loop_start: .asciz "loop start\n"
	msg_loop_end: .asciz "loop end\n"
	msg_even_start: .asciz "even start\n"
	msg_odd_start: .asciz "odd start\n"

.global _start
.text
_start:
	sub   sp, sp, #(8 * 14)
	// 调用printf
	ldr x0, addr_msg_start // x0 ← &msg_output [64-bit]
	bl printf                // call printf
	mov x1, #124           /* r1 ← 123 */
	mov x2, #0             /* r2 ← 0 */
loop:
	str   x1, [sp, #(8 * 11)]
	str   x2, [sp, #(8 * 7)]
	ldr x0, addr_msg_loop_start// x0 ← &msg_output [64-bit]
	bl printf                // call printf
	ldr   x1, [sp, #(8 * 11)]
	ldr   x2, [sp, #(8 * 7)]
	cmp x1, #1             /* compare r1 and 1 */
	beq end                /* branch to end if r1 == 1 */
 
	and x3, x1, #1         /* r3 ← r1 & 1 */
	cmp x3, #0             /* compare r3 and 0 */
	bne odd                /* branch to odd if r3 != 0 */
even:
	ldr x0, addr_msg_even_start// x0 ← &msg_output [64-bit]
	bl printf                // call printf
	//b end
odd:
	ldr x0, addr_msg_odd_start// x0 ← &msg_output [64-bit]
	bl printf                // call printf
	b end 
end:
	mov x0,x2
	mov x8, 93
	svc 0

addr_msg_start: .dword msg_start
addr_msg_end: .dword msg_end
addr_msg_loop_start: .dword msg_loop_start
addr_msg_loop_end: .dword msg_loop_end
addr_msg_odd_start: .dword msg_odd_start
addr_msg_even_start: .dword msg_even_start
