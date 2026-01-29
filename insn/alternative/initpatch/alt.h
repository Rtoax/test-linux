#pragma once
#include <stdio.h>
#include <stdint.h>

#define log(fmt...) ({	\
		int ___n = 0;	\
		___n += fprintf(stdout, "[%s]%s:%d ", __FILE__,	\
				__func__, __LINE__);	\
		___n += fprintf(stdout, fmt);	\
		___n;	\
	})


#define SEC(name) __attribute__((section(name)))

#define ALT_SECTION		".altinstructions"

#define X86_FEATURE_XMM2		( 0*32+26) /* sse2 */

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#define b_replacement(num)	"664"#num
#define e_replacement(num)	"665"#num

#define alt_end_marker		"663"
#define alt_slen		"662b-661b"
#define alt_pad_len		alt_end_marker"b-662b"
#define alt_total_slen		alt_end_marker"b-661b"
#define alt_rlen(num)		e_replacement(num)"f-"b_replacement(num)"f"

#define OLDINSTR(oldinstr, num)						\
	"# ALT: oldnstr\n"						\
	"661:\n\t" oldinstr "\n662:\n"					\
	"# ALT: padding\n"						\
	".skip -(((" alt_rlen(num) ")-(" alt_slen ")) > 0) * "		\
		"((" alt_rlen(num) ")-(" alt_slen ")),0x90\n"		\
	alt_end_marker ":\n"

#define ALTINSTR_ENTRY(feature, num)					      \
	" .long 661b - .\n"				/* label           */ \
	" .long " b_replacement(num)"f - .\n"		/* new instruction */ \
	" .word " __stringify(feature) "\n"		/* feature bit     */ \
	" .byte " alt_total_slen "\n"			/* source len      */ \
	" .byte " alt_rlen(num) "\n"			/* replacement len */ \
	" .byte " alt_pad_len "\n"			/* pad len */

#define ALTINSTR_REPLACEMENT(newinstr, feature, num)	/* replacement */	\
	"# ALT: replacement " #num "\n"						\
	b_replacement(num)":\n\t" newinstr "\n" e_replacement(num) ":\n"

/* arch/x86/include/asm/alternative.h */
#define ALTERNATIVE(oldinstr, newinstr, feature)			\
	OLDINSTR(oldinstr, 1)						\
	".pushsection .altinstructions,\"a\"\n"				\
	ALTINSTR_ENTRY(feature, 1)					\
	".popsection\n"							\
	".pushsection .altinstr_replacement, \"ax\"\n"			\
	ALTINSTR_REPLACEMENT(newinstr, feature, 1)			\
	".popsection\n"

struct alt_instr {
	int32_t instr_offset;	/* original instruction */
	int32_t repl_offset;	/* offset to replacement instruction */
	uint16_t cpuid;		/* cpuid bit set for replacement */
	uint8_t  instrlen;		/* length of original instruction */
	uint8_t  replacementlen;	/* length of new instruction */
	uint8_t  padlen;		/* length of build-time padding */
} __attribute__((packed));

struct alt_region {
	struct alt_instr *begin;
	struct alt_instr *end;
};

/* arch/x86/include/asm/barrier.h */
#define mb() asm volatile(ALTERNATIVE("lock; addl $0,-4(%%esp)", "mfence", \
				      X86_FEATURE_XMM2) ::: "memory", "cc")


void do_alt(void);

extern char __alt_instructions[], __alt_instructions_end[];

