#pragma once
#define RISCV_FENCE_ASM(p, s)		"\tfence " #p "," #s "\n"
#define RISCV_FENCE(p, s) \
	({ __asm__ __volatile__ (RISCV_FENCE_ASM(p, s) : : : "memory"); })

#define nop()		__asm__ __volatile__ ("nop")
#define __nops(n)	".rept	" #n "\nnop\n.endr\n"
#define nops(n)		__asm__ __volatile__ (__nops(n))

/* These barriers need to enforce ordering on both devices or memory. */
#define mb()		RISCV_FENCE(iorw, iorw)
#define rmb()		RISCV_FENCE(ir, ir)
#define wmb()		RISCV_FENCE(ow, ow)

/* These barriers do not need to enforce ordering on devices, just memory. */
#define smp_mb()	RISCV_FENCE(rw, rw)
#define smp_rmb()	RISCV_FENCE(r, r)
#define smp_wmb()	RISCV_FENCE(w, w)
#define smp_rwmb()	smp_mb()
