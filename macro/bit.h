#pragma once

/* Int to bit string */
#define itobs(nbits, i) \
	({\
		char __bitstr[nbits+1] = {0};\
		int __i = 0;\
		for (__i = 0; __i < nbits; __i++) {\
			__bitstr[nbits-1-__i] = i&(1<<__i)?'1':'0';\
		}\
		__bitstr;\
	})

