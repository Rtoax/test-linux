/* DPDK */
#ifndef ALLOW_EXPERIMENTAL_API
#define __rte_experimental \
	__attribute__((deprecated("Symbol is not yet part of stable ABI"), \
		section(".text.experimental")))
#else
#define __rte_experimental \
	__attribute__((section(".text.experimental")))
#endif
