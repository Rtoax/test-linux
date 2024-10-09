#pragma once
#include <stdio.h>

#define log(fmt...) ({	\
		int ___n = 0;	\
		___n += fprintf(stdout, "[%s]%s:%d ", __FILE__,	\
				__func__, __LINE__);	\
		___n += fprintf(stdout, fmt);	\
		___n;	\
	})


#define SEC(name) __attribute__((section(name)))

#define ALT_SECTION		".altinstructions"

#define __stringify_1(x...)	#x
#define __stringify(x...)	__stringify_1(x)

#define b_replacement(num)	"664"#num
#define e_replacement(num)	"665"#num

#define alt_end_marker		"663"
#define alt_slen		"662b-661b"
#define alt_pad_len		alt_end_marker"b-662b"
#define alt_total_slen		alt_end_marker"b-661b"
#define alt_rlen(num)		e_replacement(num)"f-"b_replacement(num)"f"

#define ALTERNATIVE(oldinstr, newinstr, feature)


void do_alt(void);

extern unsigned long __alt_instructions;
extern unsigned long __alt_instructions_end;

