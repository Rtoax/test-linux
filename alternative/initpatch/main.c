#include <stdio.h>
#include "alt.h"


void __attribute__((constructor)) do_alt(void)
{
	struct alt_instr *alt;
	struct alt_region region = {
		.begin	= (struct alt_instr *)__alt_instructions,
		.end	= (struct alt_instr *)__alt_instructions_end,
	};

	for (alt = region.begin; alt < region.end; alt++) {
		log("instr_offset:%x, repl_offset:%x, cpuid:%x, instrlen:%x, replacementlen:%x, padlen:%x\n",
			alt->instr_offset, alt->repl_offset, alt->cpuid,
			alt->instrlen, alt->replacementlen, alt->padlen);
	}
}

int main(void)
{
	printf("main:%p\n", main);
	mb();
	mb();
	return 0;
}
